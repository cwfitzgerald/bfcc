#include "argparser.hpp"
#include "ast.hpp"
#include "compiler.hpp"
#include "lexers/lexers.hpp"
#include "targets/targets.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#ifdef _WIN32
#define ERROR_DISPLAY_STRING "Error: "
#else
#define ERROR_DISPLAY_STRING "\033[1;31mError:\033[0m "
#endif

int main(int argc, char* argv[]) {
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
			std::cerr << ERROR_DISPLAY_STRING << "file \"" << parameters.ifilesrc << "\" can't be opened\n";
			return 2;
		}
	}

	else if (parameters.argsrc != NULL) {
		input_data = parameters.argsrc;
	}

	else {
		std::cerr << ERROR_DISPLAY_STRING << "no input files\n";
		return 2;
	}

	std::ofstream ofile;
	if (parameters.ofilesrc != NULL) {
		ofile.open(parameters.ofilesrc);
		if (ofile) {
			parameters.out = &ofile;
		}
		else {
			std::cerr << ERROR_DISPLAY_STRING << "file \"" << parameters.ofilesrc << "\" can't be opened\n";
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
			std::cerr << ERROR_DISPLAY_STRING << "file \"" << parameters.errfilesrc << "\" can't be opened\n";
			return 2;
		}
	}
	else {
		parameters.err = &std::cerr;
	}

	BFCC compiler(parameters);
	compiler.generate_ir(input_data);
	compiler.optimize();
	if (parameters.verbosity >= 2) {
		compiler.print_ir();
	}
	compiler.generate_code();
	if (!compiler.print_errors())
		*parameters.out << compiler.get_code();
}
