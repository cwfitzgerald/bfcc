#pragma once

#include "../ast.hpp"
#include <memory>
#include <vector>

enum BFCC_Symbols_Brainfuck {
		NONE, ADD, MV, LBK, RBK, PRINT, READ, NEWLINE, OTHER
};

struct BFCC_Token_Brainfuck {
	BFCC_Symbols_Brainfuck type;
	long val = 1;
};

std::vector<std::shared_ptr<BFCC_Node>> BFCC_Parser_BrainfuckLike (std::vector<BFCC_Token_Brainfuck> tokenlist);
