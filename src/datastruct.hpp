#pragma once

#include <vector>
#include <iosfwd>
#include <cinttypes>

struct BFCC_Data {
	std::vector<uint8_t> tape;
	long ptr = 0;
};

enum BFCC_ILangs : uint8_t {
	I_BF_BRAINFUCK, I_BF_TINYBF
};

enum BFCC_OLangs : uint8_t {
	O_INTERPRET, O_BF_BRAINFUCK, O_FULL_C, O_FULL_GO, O_FULL_JAVA, O_FULL_PYTHON
};

struct BFCC_Parameters {
	//I/O parameters
	char *   ifilesrc = NULL;           //Filename of input file, if null, read from STDIN
	char *     argsrc = NULL;           //Code inputed via argument
	char *   ofilesrc = NULL;           //Filename of output file, if null, write to STDOUT
	char * errfilesrc = NULL;           //Filename of error file, if null write to STDERR
	//Streams for I/O
	std::ostream* out;                  //Stream to send program output to
	std::ostream* err;                  //Stream to send error sound to
	//Options for help/debuging
	uint8_t verbosity = 0;              //How verbose the output is
	bool         cont = true;           //Flag if the program should run, false if invalid arguments
	bool        debug = false;          //Turns on debugging symbols and debug output
	//Langages to feed to/from the parser
	BFCC_ILangs ilang = I_BF_BRAINFUCK;
	BFCC_OLangs olang = O_INTERPRET;
};
