#include "opt.hpp"
#include "ir.hpp"
#include "error.hpp"
#include <algorithm>
#include <vector>



long BFCC_OP_NoOpRemoval (std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err) {
	(void) err;

	auto newend = std::remove_if(oplist.begin(), oplist.end(), [](auto x){ return x.type == NOP;});
	long rem_amount = oplist.end() - newend;
	oplist.erase(newend, oplist.end());
	return rem_amount;
}

long BFCC_OP_OperationConcatination (std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err) {
	(void) err;

	BFCC_Instruction lastop    = {oplist.front().type};
	long             lastoploc = 0;
	long             totalrem  = 0;

	for (size_t i = 0; i < oplist.size(); i++) {
		auto o  = oplist[i];
		auto ot = o.type;

		if (ot == lastop.type && (ot != JZ && ot != JNZ)) {
			lastop.data1 += o.data1;
		}
		else {
			if (lastop.type != JZ && lastop.type != JNZ) {
				oplist[lastoploc] = lastop;
				if (i+1 < oplist.size()) {
					std::fill(oplist.begin()+lastoploc+1, oplist.begin()+i, BFCC_Instruction({NOP}));
				}
				totalrem += i - lastoploc;
			}
			lastop = oplist[i];
			lastoploc = i;
		}
	}

	return totalrem;
}

long BFCC_OP_JumpRematch (std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err) {
	(void) err;

	std::vector<long> loop_indexes;
	long corrected = 0;

	for (size_t i = 0; i < oplist.size(); i++) {
		//If left side of loop, add to list of indexes
		if (oplist[i].type == JZ) {
			loop_indexes.push_back(i);
		}
		//If right side, rematch parethesis
		else if (oplist[i].type == JNZ) {
			auto leftindex = loop_indexes.back();
			//Set left op's jump
			if (oplist[leftindex].data1 != i) {
				oplist[leftindex].data1 = i;
				corrected++;
			}
			//Set right op's jump
			if (oplist[i].data1 != leftindex) {
				oplist[i].data1 = leftindex;
				corrected++;
			}
			loop_indexes.pop_back();
		}
	}

	return corrected;
}

long BFCC_OP_DeadCodeElimination (std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err) {
	long loops_removed = 0;
	auto removeloop = [&oplist, &err](long start) {
		long depth = 0;
		long end = 0;

		for (size_t i = start; i < oplist.size(); i++) {
			if (oplist[i].type == JZ) {
				depth++;
			}
			else if (oplist[i].type == JNZ) {
				depth--;
			}
			if (depth == 0) {
				end = i;
				break;
			}
		}

		std::fill(oplist.begin()+start, oplist.end()-(oplist.size()-end-1), BFCC_Instruction({NOP}));
	};

	if (oplist.front().type == JZ) {
		err.add_error("Loops at beginning of program will never be run.", oplist.front().startline, oplist.front().startchar, false);
		removeloop(0);
		loops_removed++;
	}

	BFCC_Bytecode lasttype = NOP;
	for (size_t i = 0; i < oplist.size(); i++) {
		if (oplist[i].type == JZ && lasttype == JNZ) {
			err.add_error("Loops immediatly after the end of another loop will never be run.", oplist[i].startline, oplist[i].startchar, false);
			removeloop(i);
		}
		lasttype = oplist[i].type;
	}

	return loops_removed;
}

long BFCC_OP_ClearLoopRem (std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err) {
	long loops_removed = 0;
	size_t   last_left = 0;
	bool         clean = true;

	for (size_t i = 0; i < oplist.size(); i++) {
		if (oplist[i].type == JZ) {
			last_left = i;
			clean = true;
		}
		else if (oplist[i].type == JNZ && clean == true) {
			oplist[last_left].type  = CLEAR;
			oplist[last_left].data1 = oplist[i-1].data1;
			if ((oplist[last_left].data1 % 2) == 0) {
				err.add_error("Clear loops with even subtractions might go on forever.", oplist[last_left].startline, oplist[last_left].startchar, false);
			}
			loops_removed++;
			std::fill(oplist.begin()+(i-1), oplist.begin()+(i+1), BFCC_Instruction({NOP}));
			clean = false;
		}
		else if (oplist[i].type != DADD) {
			clean = false;
		}
	}
	return loops_removed;
}

