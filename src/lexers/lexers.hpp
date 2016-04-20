#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../error.hpp"
#include "../ast.hpp"

class BFCC_Lexer {
public:
	virtual std::vector<std::shared_ptr<BFCC_Node>> gen_nodes(std::string& instr, BFCC_Error_Handler&) = 0;
};

class BFCC_Lexer_Brainfuck : public BFCC_Lexer {
public:
	std::vector<std::shared_ptr<BFCC_Node>> gen_nodes(std::string& instr, BFCC_Error_Handler&);
};