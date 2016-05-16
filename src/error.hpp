#pragma once

#include <iosfwd>
#include <string>
#include <vector>

struct BFCC_Error {
	std::string message;
	long linen;
	long charn;
	bool error;
};

class BFCC_Error_Handler {
  private:
	std::vector<BFCC_Error> errlist;
	size_t errcount = 0;
	size_t warcount = 0;

  public:
	void add_error(std::string&, long linenum, long charnum, bool err = true);
	void add_error(const char*, long linenum, long charnum, bool err = true);
	bool has_error();
	bool print_errors(std::ostream&);
};
