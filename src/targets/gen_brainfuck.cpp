#include "../ir.hpp"
#include "targets.hpp"
#include <cstdlib>
#include <memory>
#include <string>

template <char up, char down, class T>
char
char_choose(T num)
{
	if (num > 0) {
		return up;
	}
	else {
		return down;
	}
}

std::string
BFCC_Target_Brainfuck::generate(std::vector<BFCC_Instruction> ilist)
{
	long cur_offset = 0;

	auto adjust_offset = [& cur = cur_offset, this ](long newoff)
	{
		long diff  = newoff - cur;
		long adiff = std::abs(diff);

		char c = '>';
		if (diff < 0) {
			c = '<';
		}

		for (size_t i = 0; i < adiff; i++) {
			endsrc << c;
		}
		cur = newoff;
	};

	for (auto instr : ilist) {
		switch (instr.type) {
			case DPTRMV: {
				char c = char_choose<'>', '<'>(instr.data1);

				for (int i = 0; i < std::abs(instr.data1 - cur_offset); i++)
					endsrc << c;
				cur_offset = 0;
				break;
			}

			case DADD: {
				adjust_offset(instr.offset);

				char c = char_choose<'+', '-'>(instr.data1);

				for (int i = 0; i < std::abs(instr.data1); i++)
					endsrc << c;
				break;
			}

			case DPRINT:
				adjust_offset(instr.offset);

				for (int i = 0; i < instr.data1; i++)
					endsrc << '.';
				break;

			case DGET:
				adjust_offset(instr.offset);

				for (int i = 0; i < instr.data1; i++)
					endsrc << ',';
				break;

			case JZ:
				endsrc << '[';
				break;

			case JNZ:
				endsrc << ']';
				break;

			case SCAN: {
				endsrc << '[';
				char c = char_choose<'>', '<'>(instr.data1);
				for (size_t i = 0; i < std::abs(instr.data1); i++) {
					endsrc << c;
				}
				endsrc << ']';
				break;
			}

			case DDCALC:
			case DMUL:
			case NOP:
			case END:
				break;
		}
	}

	endsrc << '\n';

	return endsrc.str();
}
