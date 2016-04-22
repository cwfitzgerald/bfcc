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
	std::vector<std::shared_ptr<BFCC_Node>> nodelist;
	std::string final;

	BFCC_Parameters params; 
	BFCC_Error_Handler errhdlr;
public:
	BFCC(BFCC_Parameters& p);
	bool generate_ast(std::string);
	bool optimize ();
	bool generate_code ();
	bool print_code ();
	std::string get_code ();

	bool print_errors();
};