#include <sysexits.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

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
		std::cout << "\033[1;31mError:\033[0m file \"" << argv[1] << "\" can't be opened\n";
		return EX_NOINPUT;
	}

	
}