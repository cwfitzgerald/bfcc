#include "bf_parser.hpp"

#include <memory>
#include <vector>

std::vector<std::shared_ptr<BFCC_Node>>
BFCC_Parser_BrainfuckLike (std::vector<BFCC_Token_Brainfuck> tokenlist) {
	long curline = 1;
	long curchar = 1;

	BFCC_Token_Brainfuck lasttk = {NONE, 0};

	std::vector<std::shared_ptr<BFCC_Node>> nodelist;
	std::vector<std::shared_ptr<BFCC_Node_CTRLLoop>> loopstack;

	for (auto t : tokenlist) {
		if (t.type == lasttk.type) {
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
					break;

				case RBK:
					node = loopstack.back();
					loopstack.pop_back();
					break;
			}

			if (node) {
				if (loopstack.size() > 0) {
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

	return nodelist;
}
