#pragma once

#include "error.hpp"
#include "ir.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"
#include <memory>
#include <string>
#include <vector>

class BFCC {
  private:
	std::shared_ptr<BFCC_Lexer> lexer;
	std::shared_ptr<BFCC_Target> codegen;
	std::vector<BFCC_Instruction> ilist;
	std::string final;

	BFCC_Parameters params;
	BFCC_Error_Handler errhdlr;

  public:
	BFCC(BFCC_Parameters& p);
	bool generate_ir(std::string);
	bool optimize();
	bool generate_code();
	bool print_code();
	bool print_ir();
	std::string get_code();

	bool print_errors();
};
