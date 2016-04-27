#include "lexers.hpp"
#include "../ast.hpp"
#include "../parsers/bf_parser.hpp"
#include <string>
#include <vector>
#include <memory>

std::vector<std::shared_ptr<BFCC_Node>>
BFCC_Lexer_Brainfuck::gen_nodes(std::string& instr) {
	std::vector<BFCC_Token_Brainfuck> tokenlist;
	tokenlist.reserve(instr.size());

	for (char c : instr) {
		BFCC_Token_Brainfuck t;

		switch (c) {
			case '-':
				t.val = -1;
			case '+': //Fallthrough
				t.type = ADD;
				break;

			case '<':
				t.val = -1;
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

	return BFCC_Parser_BrainfuckLike(tokenlist, err);
}