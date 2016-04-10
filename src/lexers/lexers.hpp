#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../ast.hpp"

class BFCC_Lexer {
public:
	virtual std::vector<std::shared_ptr<BFCC_Node>> gen_node(std::string& instr) = 0;
};

class BFCC_Lexer_Brainfuck : public BFCC_Lexer {
public:
	std::vector<std::shared_ptr<BFCC_Node>> gen_node(std::string& instr);
};