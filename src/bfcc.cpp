#include <sysexits.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include "ast.hpp"
#include "argparser.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"

int main (int argc, char * argv[]) {
	auto parameters = argparser(argc, argv);
	if (parameters.cont == false) {
		return 1;
	}

	std::string input_data;
	if (parameters.ifilesrc != NULL) {
		std::ifstream ifile (parameters.ifilesrc); 
		if (ifile) {  
			std::stringstream ss;
			ss << ifile.rdbuf();
			input_data = ss.str();
		}
		else {
			std::cerr << "\033[1;31mError:\033[0m file \"" << argv[1] << "\" can't be opened\n";
			return 2;
		}
	}

	else if (parameters.argsrc != NULL) {
		input_data = parameters.argsrc;
	}

	else {
		while (!std::cin.eof()) {
			char c = std::cin.get();
			input_data += c;
		}
	}

	std::cout << input_data << std::endl;

	/*
	std::shared_ptr<BFCC_Lexer> lexer = std::make_shared<BFCC_Lexer_Brainfuck>();
	auto nodelist = lexer->gen_node(input_data);

	std::cout << nodelist.size();

	std::shared_ptr<BFCC_Target> target = std::make_shared<BFCC_Target_Brainfuck>();
	for (auto i : nodelist) {
		i->accept(static_cast<std::shared_ptr<BFCC_Visitor>>(target));
	}
	std::cout << target->gen_target();
	std::cout << std::endl;*/
}