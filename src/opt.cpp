#include "opt.hpp"
#include "ir.hpp"
#include <algorithm>
#include <vector>

long BFCC_OP_NoOpRemoval (std::vector<BFCC_Instruction>& oplist) {
	auto newend = std::remove_if(oplist.begin(), oplist.end(), [](auto x){ return x.type == NOP;});
	long rem_amount = oplist.end() - newend;
	oplist.erase(newend, oplist.end());
	return rem_amount;
}

long BFCC_OP_OperationConcatination (std::vector<BFCC_Instruction>& oplist) {
	BFCC_Instruction lastop    = {oplist.front().type};
	long             lastoploc = 0;
	long             totalrem  = 0;

	for (int i = 0; i < oplist.size(); i++) {
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

long BFCC_OP_JumpRematch (std::vector<BFCC_Instruction>& oplist) {
	std::vector<long> loop_indexes;
	long corrected = 0;

	for (int i = 0; i < oplist.size(); i++) {
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
