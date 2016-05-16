#include "../ir.hpp"
#include "targets.hpp"
#include <chrono>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <string>

std::string
BFCC_Target_Interpreter::generate(std::vector<BFCC_Instruction> ilist)
{
	std::vector<uint8_t> data(32768 + 16, 0);
	size_t dptr = 0;

	size_t multiplication_cache = 1;

	auto checkptr = [&dptr]() { dptr &= 32767; };

	auto icp = [](auto num) { return num & 32767; };

	// Timing stuffs
	auto start_clock			   = std::chrono::high_resolution_clock::now();
	uint64_t instructions_executed = 0;

	auto instruction_count = ilist.size();
	for (size_t iptr = 0; iptr < instruction_count; iptr++) {
		// std::cout << iptr << "\n";
		switch (ilist[iptr].type) {
			case DPTRMV:
				dptr += ilist[iptr].data1;
				checkptr();
				break;

			case DADD:
				data[icp(dptr + ilist[iptr].offset)] += ilist[iptr].data1;
				break;

			case DPRINT:
				for (int i = 0; i < ilist[iptr].data1; i++) {
					params.out->put(static_cast<char>(data[icp(dptr + ilist[iptr].offset)]));
				}
				break;

			case DGET:
				if (ilist[iptr].data1 > 1) {
					std::cin.ignore(ilist[iptr].data1 - 1);
				}

				char c;
				if (std::cin.get(c)) {
					data[icp(dptr + ilist[iptr].offset)] = static_cast<uint8_t>(c);
				}
				else {
					data[icp(dptr + ilist[iptr].offset)] = 0;
				}

				break;

			case JZ:
				if (data[dptr] == 0) {
					iptr = ilist[iptr].data1;
				}
				break;

			case JNZ:
				if (data[dptr] != 0) {
					iptr = ilist[iptr].data1;
				}
				break;

			case DDCALC:
				// If current cell odd and decrement amount are even
				// it's an infinite loop
				if ((data[dptr] & 1) == 1 && (ilist[iptr].data1 & 1) == 0) {
					errhdlr->add_error("Runtime Error! Infinite balanced loop. Check for a warning.", -1, -1);
					iptr = ilist.size();
				}
				else {
					multiplication_cache = data[dptr];
					while ((multiplication_cache % ilist[iptr].data1) != 0) {
						multiplication_cache += 256;
					}
				}
				break;

			case DMUL: {
				size_t loop_count = data[dptr];
				if (ilist[iptr].data2) {
					loop_count = multiplication_cache;
				}

				size_t cell = icp(dptr + ilist[iptr].offset);
				data[cell] += (ilist[iptr].data1 * loop_count);
				break;
			}

			case SCAN:
				while (data[dptr] != 0) {
					dptr = icp(dptr + ilist[iptr].data1);
				}

			case NOP:
			case END:
				break;
		}
		instructions_executed++;
	}

	auto end_clock = std::chrono::high_resolution_clock::now();
	auto totaltime = end_clock - start_clock;
	std::cerr << "\nThe interpreter took " << static_cast<double>(totaltime.count()) / 1'000'000'000
			  << " seconds to run a " << ilist.size() << " instruction program"
			  << "\n"
			  << instructions_executed << " instructions were executed."
			  << "\n"
			  << static_cast<double>(totaltime.count()) / instructions_executed << " ns per instruction. ("
			  << instructions_executed / (static_cast<double>(totaltime.count()) / 1'000'000'000)
			  << " instructions per second)"
			  << "\n";

	return "";
}
