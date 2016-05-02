#pragma once

#include <string> 
#include <vector>
#include <iostream>

struct BFCC_Error {
	std::string message;
	long linen;
	long charn;
	bool error;
};

class BFCC_Error_Handler {
private:
	std::vector<BFCC_Error> errlist;
	bool haserr = false;
public:
	void add_error(std::string&, long linenum, long charnum, bool err=true);
	void add_error(const char *, long linenum, long charnum, bool err=true);
	bool has_error();
	bool print_errors(std::ostream& = std::cerr);
};
