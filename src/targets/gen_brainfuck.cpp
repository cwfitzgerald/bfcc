#include <cstdlib>
#include <memory>
#include <string>
#include "targets.hpp"
#include "../ir.hpp"

std::string BFCC_Target_Brainfuck::generate(std::vector<BFCC_Instruction> ilist) {
	for (auto instr : ilist) {
		switch (instr.type) {
			case DPTRMV: {
				char c = '>';
				if (instr.data1 < 0)
					c = '<';

				for (int i = 0; i < labs(instr.data1); i++)
					endsrc += c;
				break;
			}

			case DADD: {
				char c = '+';
				if (instr.data1 < 0)
					c = '-';

				for (int i = 0; i < labs(instr.data1); i++) 
					endsrc += c;
				break;
			}

			case DPRINT:
				for (int i = 0; i < instr.data1; i++)
					endsrc += '.';
				break;

			case DGET:
				for (int i = 0; i < instr.data1; i++)
					endsrc += ',';
				break;

			case JZ:
				endsrc += '[';
				break;

			case JNZ:
				endsrc += ']';
				break;

			case NOP:
			case END:
				break;
		}
	}

	return endsrc;
}
