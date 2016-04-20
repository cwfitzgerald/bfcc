#pragma once

#include <memory>
#include <vector>
#include <string>
#include "error.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"
#include "optimizers/optimizers.hpp"

class BFCC {
private:
	std::shared_ptr<BFCC_Lexer> lexer;
	std::shared_ptr<BFCC_Target> codegen;
	std::vector<std::shared_ptr<BFCC_Optimizer>> optimizers;
	BFCC_Parameters params; 
	BFCC_Error_Handler errhdlr;
public:
	BFCC (BFCC_Parameters& p);
	bool lex(std::string);
};