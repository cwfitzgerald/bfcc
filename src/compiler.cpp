#include "compiler.hpp"
#include "datastruct.hpp"
#include "lexers/lexers.hpp"
#include "opt.hpp"
#include "targets/targets.hpp"
#include <iostream>
#include <memory>

BFCC::BFCC(BFCC_Parameters& p)
{
	// Set internal parameters
	params = p;

	// Set source language
	switch (params.ilang) {
		case I_BF_BRAINFUCK:
			lexer = std::make_shared<BFCC_Lexer_Brainfuck>(params, errhdlr);
			break;
		case I_BF_TINYBF:
			errhdlr.add_error("Source language tinybf is not currently supported.", 0, 0, true);
			break;
	}

	// Set target language
	switch (params.olang) {
		case O_INTERPRET:
			codegen = std::make_shared<BFCC_Target_Interpreter>(params, errhdlr);
			break;
		case O_BF_BRAINFUCK:
			codegen = std::make_shared<BFCC_Target_Brainfuck>(params, errhdlr);
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

bool
BFCC::generate_ir(std::string instr)
{
	// The compiling process can't continue if there is an error
	if (errhdlr.has_error()) {
		return false;
	}

	auto nodelist = lexer->gen_nodes(instr);
	BFCC_AST_to_IR ati(params, errhdlr);
	ilist = ati.generate(nodelist);

	return errhdlr.has_error();
}

bool
BFCC::optimize()
{
	if (errhdlr.has_error()) {
		return false;
	}

	BFCC_OP_OperationConcatination(ilist, errhdlr);
	BFCC_OP_DeadCodeElimination(ilist, errhdlr);
	BFCC_OP_NoOpRemoval(ilist, errhdlr);
	BFCC_OP_LazyMoves(ilist, errhdlr);
	BFCC_OP_MultiplyLoopRem(ilist, errhdlr);
	BFCC_OP_ScanLoopRem(ilist, errhdlr);

	return true;
}

bool
BFCC::generate_code()
{
	if (errhdlr.has_error()) {
		return false;
	}

	final = codegen->generate(ilist);

	return errhdlr.has_error();
}

std::string
BFCC::get_code()
{
	return final;
}

bool
BFCC::print_ir()
{
	if (errhdlr.has_error()) {
		return false;
	}

	*params.err << BFCC_IR_PPrint(ilist);

	return true;
}

bool
BFCC::print_code()
{
	*params.out << final << std::endl;

	return true;
}

bool
BFCC::print_errors()
{
	return errhdlr.print_errors(*params.err);
}
