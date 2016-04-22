#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include "ast.hpp"
#include "argparser.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"
#include "compiler.hpp"

int main (int argc, char * argv[]) {
	auto parameters = argparser(argc, argv);
	if (parameters.cont == false) {
		return 1;
	}

	std::string input_data;
	std::ifstream ifile; 
	if (parameters.ifilesrc != NULL) {
		ifile.open(parameters.ifilesrc);
		if (ifile) {  
			std::stringstream ss;
			ss << ifile.rdbuf();
			input_data = ss.str();
		}
		else {
			std::cerr << "\033[1;31mError:\033[0m file \"" << parameters.ifilesrc << "\" can't be opened\n";
			return 2;
		}
	}

	else if (parameters.argsrc != NULL) {
		input_data = parameters.argsrc;
	}

	else {
		while (!std::cin.eof()) {
			char c = std::cin.get();
			if (!std::cin.eof()) {
				input_data += c;
			}
		}
	}


	std::ofstream ofile;
	if (parameters.ofilesrc != NULL) {
		ofile.open(parameters.ofilesrc);
		if (ofile) {
			parameters.out = &ofile;
		}
		else {
			std::cerr << "\033[1;31mError:\033[0m file \"" << parameters.ofilesrc << "\" can't be opened\n";
			return 2;
		}
	}
	else {
		parameters.out = &std::cout;
	}


	std::ofstream errfile;
	if (parameters.errfilesrc != NULL) {
		errfile.open(parameters.errfilesrc);
		if (errfile) {
			parameters.err = &errfile;
		}
		else {
			std::cerr << "\033[1;31mError:\033[0m file \"" << parameters.errfilesrc << "\" can't be opened\n";
			return 2;
		}
	}
	else {
		parameters.err = &std::cerr;
	}
	/*
	std::shared_ptr<BFCC_Lexer> lexer = std::make_shared<BFCC_Lexer_Brainfuck>();
	BFCC_Error_Handler e;
	auto nodelist = lexer->gen_nodes(input_data, e);

	*parameters.err << nodelist.size() << std::endl;

	std::shared_ptr<BFCC_Target> target = std::make_shared<BFCC_Target_Brainfuck>();
	for (auto i : nodelist) {
		i->accept(static_cast<std::shared_ptr<BFCC_Visitor>>(target));
	}
	*parameters.out << target->gen_target();
	*parameters.out << std::endl;
	*/

	BFCC compiler (parameters);
	compiler.generate_ast(input_data);
	compiler.optimize();
	compiler.generate_code();
	if (!compiler.print_errors())
		std::cout << compiler.get_code() << std::endl;
}
