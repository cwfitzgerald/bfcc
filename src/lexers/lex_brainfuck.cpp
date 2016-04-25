#include "lexers.hpp"
#include "../ast.hpp"
#include <string>
#include <vector>
#include <memory>

std::vector<std::shared_ptr<BFCC_Node>>
BFCC_Lexer_Brainfuck::gen_nodes(std::string& instr, BFCC_Error_Handler& err) {
	std::vector<std::shared_ptr<BFCC_Node>> node_list;

	(void) err;

	long curc = 0;
	long curl = 0;

	char lastchr = '\0';
	long samecnt = 0;

	enum bfsymbols {
			ADD, MV, LBK, RBK, PRINT, READ, NEWLINE, OTHER
	};

	struct bftoken {
		bfsymbols type;
		bool neg = false;
	};

	std::vector<bftoken> tokenlist;
	tokenlist.reserve(instr.size());

	for (char c : instr) {
		bftoken t;

		switch (c) {
			case '-':
				t.neg = true;
			case '+': //Fallthrough
				t.type = ADD;
				break;

			case '<':
				t.neg = true;
			case '>': //Fallthrough
				t.type = MV;
				break;

			case ',':
				t.type = READ;
				break;
			case '.':
				t.type = PRINT;
				break;

			case '[':
				t.type = LBK;
				break;
			case ']':
				t.type = RBK;
				break;

			case '\n':
				t.type = NEWLINE;
				break;

			default:
				t.type = OTHER;
				break;
		}

		tokenlist.push_back(t);
	}

	return node_list;
}