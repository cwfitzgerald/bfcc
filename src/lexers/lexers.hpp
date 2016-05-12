#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../datastruct.hpp"
#include "../error.hpp"
#include "../ast.hpp"

class BFCC_Lexer {
protected:
	BFCC_Parameters params;
	BFCC_Error_Handler* err;
public:
	BFCC_Lexer(BFCC_Parameters& p, BFCC_Error_Handler& e) {
		params = p;
		err = &e;
	};
	virtual std::vector<std::shared_ptr<BFCC_Node>> gen_nodes(std::string& instr) = 0;
};

class BFCC_Lexer_Brainfuck : public BFCC_Lexer {
public:
	BFCC_Lexer_Brainfuck(BFCC_Parameters& p, BFCC_Error_Handler& e) : BFCC_Lexer(p,e) {};
	std::vector<std::shared_ptr<BFCC_Node>> gen_nodes(std::string& instr);
};
