#include "lexers.hpp"
#include <string>
#include <memory>

std::vector<std::shared_ptr<BFCC_AST_Node>>
BFCC_Lexer_Brainfuck::generate(std::string& instr) {
	std::vector<std::shared_ptr<BFCC_AST_Node>> node_list;

	for (char c : instr) {
		switch (c) {
			case '+':
				break;
			case '-':
				break;
			case '>':
				break;
			case '<':
				break;
			case '[':
				break;
			case ']':
				break;
			case '.':
				break;
			case ',':
				break;
		}
	}

	return node_list;
}