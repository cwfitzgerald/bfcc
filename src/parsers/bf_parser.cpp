#include "bf_parser.hpp"
#include "../error.hpp"

#include <memory>
#include <vector>
#include <tuple>

std::vector<std::shared_ptr<BFCC_Node>>
BFCC_Parser_BrainfuckLike (std::vector<BFCC_Token_Brainfuck> tokenlist, BFCC_Error_Handler& err) {
	long curline = 1;
	long curchar = 1;

	BFCC_Token_Brainfuck lasttk = {NONE, 0};

	std::vector<std::shared_ptr<BFCC_Node>> nodelist;
	std::vector<std::shared_ptr<BFCC_Node_CTRLLoop>> loopstack;
	std::vector<std::tuple<long, long>> loopstartlocations;

	for (auto t : tokenlist) {
		if (t.type == lasttk.type && t.type != LBK && t.type != RBK) {
			lasttk.val += t.val;
		}
		else {
			std::shared_ptr<BFCC_Node> node;

			switch (lasttk.type) {
				case ADD:
					node = std::make_shared<BFCC_Node_DATAadd> (lasttk.val);
					break;

				case MV:
					node = std::make_shared<BFCC_Node_DPTRmv> (lasttk.val);
					break;

				case PRINT:
					node = std::make_shared<BFCC_Node_DATAprint> (lasttk.val);
					break;

				case READ:
					node = std::make_shared<BFCC_Node_DATAget> (lasttk.val);
					break;

				case LBK:
					loopstack.push_back(std::make_shared<BFCC_Node_CTRLLoop>());
					loopstartlocations.push_back(std::make_tuple(curline, curchar));
					break;

				case RBK:
					if (loopstack.size()) {
						node = loopstack.back();
						loopstack.pop_back();
						loopstartlocations.pop_back();
					}
					else {
						err.add_error("Unmatched \"]\"", curline, curchar, true);
					}
					break;
			}

			if (node) {
				if (loopstack.size()) {
					loopstack.back()->add(node);
				}
				else {
					nodelist.push_back(node);
				}
			}

			lasttk = t;
		}

		//Deal with current location
		if (t.type == NEWLINE) {
			curline++;
			curchar = 1;
		}
		else {
			curchar++;
		}
	}

	while (loopstack.size()) {
		err.add_error("Unmatched \"[\"", std::get<0>(loopstartlocations.back()), std::get<1>(loopstartlocations.back()), false);

		auto node = loopstack.back();
		loopstack.pop_back();
		loopstartlocations.pop_back();

		if (loopstack.size() > 1) {
			loopstack.back()->add(node);
		}
		else {
			nodelist.push_back(node);
		}
	}

	return nodelist;
}
