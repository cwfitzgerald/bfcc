#include <sysexits.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include "ast.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"

int main (int argc, char * argv[]) {
	if (argc != 2) {
		std::cerr << "\033[1;31mError:\033[0m invalid amount of argument" << std::endl;
		return EX_USAGE;
	}

	std::string input_data;
	std::ifstream ifile (argv[1]);
	if (ifile) {
		std::stringstream ss;
		ss << ifile.rdbuf();
		input_data = ss.str();
		ifile.close();
	}
	else {
		std::cerr << "\033[1;31mError:\033[0m file \"" << argv[1] << "\" can't be opened\n";
		return EX_NOINPUT;
	}

	std::shared_ptr<BFCC_Lexer> lexer = std::make_shared<BFCC_Lexer_Brainfuck>();
	auto nodelist = lexer->gen_node(input_data);

	std::cout << nodelist.size();

	std::shared_ptr<BFCC_Target> target = std::make_shared<BFCC_Target_Brainfuck>();
	for (auto i : nodelist) {
		i->accept(static_cast<std::shared_ptr<BFCC_Visitor>>(target));
		//std::cout << i->get_type();
	}
	std::cout << target->gen_target();
	std::cout << std::endl;
	
}