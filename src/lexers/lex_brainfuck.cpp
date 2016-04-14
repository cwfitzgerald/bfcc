#include "lexers.hpp"
#include "../ast.hpp"
#include <string>
#include <memory>

std::vector<std::shared_ptr<BFCC_Node>>
BFCC_Lexer_Brainfuck::gen_nodes(std::string& instr) {
	std::vector<std::shared_ptr<BFCC_Node>> node_list;

	long curc = 0;
	long curl = 0;

	for (char c : instr) {
		std::shared_ptr<BFCC_Node> node; 

		switch (c) {
			case '+':
				node = std::make_shared<BFCC_Node_RAWAdd>();
				break;
			case '-':
				node = std::make_shared<BFCC_Node_RAWSub>();
				break;
			case '>':
				node = std::make_shared<BFCC_Node_RAWLeft>();
				break;
			case '<':
				node = std::make_shared<BFCC_Node_RAWRight>();
				break;
			case '[':
				node = std::make_shared<BFCC_Node_RAWLeftbrk>();
				break;
			case ']':
				node = std::make_shared<BFCC_Node_RAWRightbrk>();
				break;
			case '.':
				node = std::make_shared<BFCC_Node_RAWDot>();
				break;
			case ',':
				node = std::make_shared<BFCC_Node_RAWComma>();
				break;
			case '\n':
				curl++;
				curc=0;
				continue;
			default:
				curc++;
				continue;
		}

		node->set_data(curl, curc, curl, curc+1);

		curc++;
		node_list.push_back(node);
	}

	return node_list;
}