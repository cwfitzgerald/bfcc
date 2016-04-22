#include <algorithm>
#include <string>
#include <iostream>
#include "error.hpp"

void BFCC_Error_Handler::add_error(std::string& instr, long linenum, long charnum, bool err) {
	errlist.push_back({instr, linenum, charnum, err});
	if (err)
		haserr = true;
}

void BFCC_Error_Handler::add_error(const char * instr, long linenum, long charnum, bool err) {
	errlist.push_back({instr, linenum, charnum, err});
	if (err)
		haserr = true;
}

bool BFCC_Error_Handler::print_errors(std::ostream& err) {
	auto sorterr = [](BFCC_Error left, BFCC_Error right) {
		return (left.linen < right.linen || (left.linen == right.linen && left.charn < right.charn));
	};

	//Sort by line number then character number of the error
	std::sort(errlist.begin(), errlist.end(), sorterr);

	for (auto e : errlist) {
		if (e.error) {
			err << "\033[1;31mError\033[0m";
		}
		else {
			err << "\033[1;35mWarning\033[0m";
		}
		err << " at Line " << e.linen << " Char " << e.charn << ": " << e.message << "\n";
	}

	return haserr;
}

bool BFCC_Error_Handler::has_error() {
	return haserr;
}