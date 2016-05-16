#include "opt.hpp"
#include "datastruct.hpp"
#include "error.hpp"
#include "ir.hpp"
#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>

long
BFCC_OP_NoOpRemoval(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	(void) err;

	auto newend		= std::remove_if(oplist.begin(), oplist.end(), [](auto x) { return x.type == NOP; });
	long rem_amount = oplist.end() - newend;
	oplist.erase(newend, oplist.end());

	BFCC_OP_JumpRematch(params, oplist, err);

	return rem_amount;
}

long
BFCC_OP_OperationConcatination(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	(void) err;

	if (params.fdeadcodeelimination == false) {
		return 0;
	}

	BFCC_Instruction lastop = { oplist.front().type };
	long lastoploc			= 0;
	long totalrem			= 0;

	for (size_t i = 0; i < oplist.size(); i++) {
		auto o  = oplist[i];
		auto ot = o.type;

		if (ot == lastop.type && (ot != JZ && ot != JNZ)) {
			lastop.data1 += o.data1;
		}
		else {
			if (lastop.type != JZ && lastop.type != JNZ) {
				oplist[lastoploc] = lastop;
				if (i + 1 < oplist.size()) {
					std::fill(oplist.begin() + lastoploc + 1, oplist.begin() + i, BFCC_Instruction({ NOP }));
				}
				totalrem += i - lastoploc;
			}
			lastop	= oplist[i];
			lastoploc = i;
		}
	}

	BFCC_OP_NoOpRemoval(params, oplist, err);

	return totalrem;
}

long
BFCC_OP_JumpRematch(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	(void) err;
	(void) params;

	std::vector<long> loop_indexes;
	long corrected = 0;

	for (size_t i = 0; i < oplist.size(); i++) {
		// If left side of loop, add to list of indexes
		if (oplist[i].type == JZ) {
			loop_indexes.push_back(i);
		}
		// If right side, rematch parethesis
		else if (oplist[i].type == JNZ) {
			auto leftindex = loop_indexes.back();
			// Set left op's jump
			if (oplist[leftindex].data1 != i) {
				oplist[leftindex].data1 = i;
				corrected++;
			}
			// Set right op's jump
			if (oplist[i].data1 != leftindex) {
				oplist[i].data1 = leftindex;
				corrected++;
			}
			loop_indexes.pop_back();
		}
	}

	return corrected;
}

long
BFCC_OP_DeadCodeElimination(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	long loops_removed = 0;
	auto removeloop	= [&params, &oplist, &err](long start) {
		if (params.fdeadcodeelimination == false) {
			return;
		}

		long depth = 0;
		long end   = 0;

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

		std::fill(oplist.begin() + start, oplist.end() - (oplist.size() - end - 1), BFCC_Instruction({ NOP }));
	};

	if (oplist.front().type == JZ) {
		err.add_error("Loops at beginning of program will never be run.", oplist.front().startline,
					  oplist.front().startchar, false);
		removeloop(0);
		loops_removed++;
	}

	BFCC_Bytecode lasttype = NOP;
	for (size_t i = 0; i < oplist.size(); i++) {
		if (oplist[i].type == JZ && lasttype == JNZ) {
			err.add_error("Loops immediatly after the end of another loop will never be run.", oplist[i].startline,
						  oplist[i].startchar, false);
			removeloop(i);
		}
		lasttype = oplist[i].type;
	}

	BFCC_OP_NoOpRemoval(params, oplist, err);

	return loops_removed;
}

long
BFCC_OP_LazyMoves(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	(void) err;

	if (params.flazymoves == 0) {
		return 0;
	}

	long mv_removed = 0;

	auto offsetable = [](BFCC_Instruction i) { return ((i.type == DADD) || (i.type == DPRINT) || (i.type == DGET)); };

	std::vector<BFCC_Instruction> new_oplist;
	new_oplist.reserve(oplist.size());
	int64_t curoffset = 0;
	for (auto o : oplist) {
		if (offsetable(o)) {
			auto tmp   = o;
			tmp.offset = curoffset;
			new_oplist.push_back(tmp);
		}
		else if (o.type == DPTRMV) {
			curoffset += o.data1;
			mv_removed++;
		}
		else {
			if (curoffset) {
				new_oplist.push_back({ DPTRMV, curoffset });
				curoffset = 0;
			}
			new_oplist.push_back(o);
		}
	}

	oplist = new_oplist;

	BFCC_OP_JumpRematch(params, oplist, err);

	return mv_removed;
}

long
BFCC_OP_MultiplyLoopRem(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	long loops_removed = 0;
	size_t last_left   = 0;
	bool clean		   = true;

	for (size_t i = 0; i < oplist.size(); i++) {
		if (oplist[i].type == JZ) {
			last_left = i;
			clean	 = true;
		}
		// Clean says that the loop is mearly composed of moves and adds.
		else if (oplist[i].type == JNZ && clean == true) {
			std::vector<int64_t> effects;
			size_t startoffset = 0;

			// Find the furthest left and right the loop goes
			// in order to make the effect vector (and access offset)
			// the correct size.
			auto left_itterator  = oplist.begin() + last_left + 1; // Left is inclusive
			auto right_itterator = oplist.begin() + i;			   // Right is exclusive
			auto itterator		 = left_itterator;
			int64_t leftmost	 = 0;
			int64_t rightmost	= 0;

			int64_t cur		= 0;
			int64_t working = 0;
			while (itterator != right_itterator) {
				if (itterator->type == DPTRMV) {
					cur += itterator->data1;
					working = cur;
				}
				else if (itterator->type == DADD) {
					working = cur + itterator->offset;
				}
				if (working < leftmost) {
					leftmost = working;
				}
				else if (rightmost < working) {
					rightmost = working;
				}
				itterator++;
			}

			effects.resize(rightmost - leftmost + 1, 0);
			startoffset = std::abs(leftmost);

			// if the loop is balanced unroll loop
			if (cur == 0) {
				// Calculate effects of the loop
				itterator = left_itterator;
				working   = 0;

				while (itterator != right_itterator) {
					if (itterator->type == DPTRMV) {
						cur += itterator->data1;
						working = cur;
					}
					else if (itterator->type == DADD) {
						working = cur + itterator->offset;
						effects[working + startoffset] += itterator->data1;
					} /*
					 if (itterator->type == DADD) {
						 cur		= itterator->offset;
						 working = cur;
						 effects[cur + startoffset] += itterator->data1;
					 }*/
					itterator++;
				}

				/*for (auto pI : effects)
					std::cout << pI << " ";
				std::cout << "\n";*/
			}
			else {
				clean = false;
				continue;
			}

			// Check if it's optimizable
			int64_t denominator = std::abs(effects[startoffset]);

			if (effects[startoffset] > 0) {
				clean = false;
				continue;
			}
			else if (effects[startoffset] == 0) {
				err.add_error("Balanced loops which never decrement the starting cell will be infinite.",
							  left_itterator->startline, left_itterator->startchar - 1);
				clean = false;
				continue;
			}
			else if ((effects[startoffset] & 1) == 0) {
				err.add_error("Balanced loops which decrement the starting cell by an even number will be infinite if "
							  "current cell is odd.",
							  left_itterator->startline, left_itterator->startchar - 1, false);
			}

			// If allowed, actually optimize
			if (params.fmultiplyloop == false) {
				clean = false;
				continue;
			}

			// Take the information on the loop and actually
			// unroll the loop.
			itterator = left_itterator - 1; // Overwrite the jump command

			// Loops that decrement start by more than one need special
			// calculations done to figure out how many times the loop
			// actauly runs
			if (denominator > 1) {
				*itterator = { DDCALC, denominator };
				itterator++;
			}
			for (size_t j = 0; itterator != right_itterator + 1; j++) {
				if (j < effects.size()) {
					if (effects[j] != 0 && j != startoffset) {
						*itterator = { DMUL, effects[j], denominator > 1, static_cast<long>(j - startoffset) };
						itterator++;
					}
				}
				else {
					*itterator = { NOP };
					itterator++;
				}
			}
			*(--itterator) = { DMUL, -1, denominator > 1, 0 };

			clean = false;
		}
		else if (oplist[i].type != DADD && oplist[i].type != DPTRMV) {
			clean = false;
		}
	}

	BFCC_OP_NoOpRemoval(params, oplist, err);

	return loops_removed;
}

long
BFCC_OP_ScanLoopRem(BFCC_Parameters& params, std::vector<BFCC_Instruction>& oplist, BFCC_Error_Handler& err)
{
	if (params.fscanloop == false) {
		return 0;
	}

	long loops_removed = 0;
	size_t last_left   = 0;
	bool clean		   = true;

	for (size_t i = 0; i < oplist.size(); i++) {
		if (oplist[i].type == JZ) {
			last_left = i;
			clean	 = true;
		}
		// Clean says that the loop is mearly composed of moves.
		else if (oplist[i].type == JNZ && clean == true && params.fscanloop) {
			auto& tmp			  = oplist[last_left];
			tmp.type			  = SCAN;
			tmp.data1			  = oplist[last_left + 1].data1;
			oplist[last_left + 1] = { NOP };
			oplist[i]			  = { NOP };

			clean = false;
		}
		else if (oplist[i].type != DPTRMV) {
			clean = false;
		}
	}

	BFCC_OP_NoOpRemoval(params, oplist, err);

	return loops_removed;
}
