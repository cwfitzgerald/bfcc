#include <memory>
#include "compiler.hpp"
#include "datastruct.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"

BFCC::BFCC(BFCC_Parameters& p) {
	//Set internal parameters
	params = p;

	//Set source language
	switch (params.ilang) {
		case I_BF_BRAINFUCK:
			lexer = std::make_shared<BFCC_Lexer_Brainfuck>();
			break;
		case I_BF_TINYBF:
			errhdlr.add_error("Source language tinybf is not currently supported.", 0, 0, true);
			break;
	}

	//Set target language
	switch (params.olang) {
		case O_INTERPRET:
			errhdlr.add_error("The interpreter is not currently supported", 0, 0, true);
			break;
		case O_BF_BRAINFUCK:
			codegen = std::make_shared<BFCC_Target_Brainfuck>();
			break;
		case O_FULL_C:
			errhdlr.add_error("The target language C is not currently supported.", 0, 0, true);
			break;
		case O_FULL_GO:
			errhdlr.add_error("The target language Go is not currently supported.", 0, 0, true);
			break;
		case O_FULL_JAVA:
			errhdlr.add_error("The target language Java is not currently supported.", 0, 0, true);
			break;
		case O_FULL_PYTHON:
			errhdlr.add_error("The target language Python is not currently supported.", 0, 0, true);
			break;
	}
}

bool BFCC::lex (std::string instr) {
	//The compiling process can't continue if there is an error
	if (errhdlr.has_error()) {
		return false;
	}

	lexer->gen_nodes(instr, errhdlr);

	return errhdlr.has_error();
}