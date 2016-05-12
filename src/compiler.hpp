#pragma once

#include <memory>
#include <vector>
#include <string>
#include "error.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"
#include "ir.hpp"

struct BFCC_Loop_Data {
	           size_t start_index;
	             bool multiply;
	std::vector<long> effects;
	           size_t eoffset;
};

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
	bool generate_ir (std::string);
	bool optimize ();
	bool generate_code ();
	bool print_code ();
	bool print_ir();
	std::string get_code ();

	bool print_errors();
};
