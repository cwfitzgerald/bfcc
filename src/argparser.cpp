#include "datastruct.hpp"
#include <iostream>
#include <cstring>

BFCC_Parameters argparser(int argc, char * argv[]) {
	BFCC_Parameters p;

	auto display_help = [&argv]() {
		std::cerr << "Usage:\n" << 
		argv[0] << " [options] -i [inputfile] -o [outputfile]\n\n" <<
		"I/O Options:\n"
		"  -i, --input-file <filename>    Set file to read the program from\n"
		"  -o, --output-file <filename>   Set file to write final program to\n"
		"  -e, --error-file <filename>    Set file to redirect errors to\n"
		"  -c, --code <program>           Run the program given\n"
		"If no input is found: input will be read from STDIN\n"
		"                      output will be written to STDOUT\n"
		"                      errors will be written to STDERR\n"
		"Language Options:\n"
		"  -l, --language <language>      Set the input language (default: brainfuck)\n"
		"  -t, --target <language>        Set the target language (default: interpreter)\n"
		"      --list-languages           List all available input/target languages\n"
		"Debug Options:\n"
		"  -v, --verbose <level>          Set verbosity level (0-3)\n"
		"  -d, --debug                    Turn on debuging: (Memory Dumps: #)\n"
		"  -h, --help                     Print this message\n"
		;

	};

	auto list_languages = []() {
		std::cerr << "List of supported languages:\n\n" <<
		"L.. = Lexing supported (you can compile this language)\n"
		".T. = Targetting/Codegen supported (you can compile to this language\n"
		"..P = Pritty print supported (output code is formatted correctly\n\n"

		"Brainfuck dirivities:\n"
		"LT. - brainfuck\n"
		"... - tinybf\n"
		"Full langages:\n"
		".TP - c\n" 
		".TP - go\n"
		".TP - java\n"
		".TP - python\n"
		;

	};

	//Iterate through all arguments
	//p.cont stores if the program should continue after parsing arguments
	//or if it should quit due to an argument error.
	for (int i = 1; i < argc; i++) {

		//Flags with arguments
		if (i+1 < argc) {
			//Input files
			if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input-file") == 0) {
				p.ifilesrc = argv[++i];
				continue;
			}

			//Output file
			else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-file") == 0) {
				p.ofilesrc = argv[++i];
				continue;
			}

			//Error file
			else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--error-file") == 0) {
				p.errfilesrc = argv[++i];
				continue;
			}

			//Input code
			else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--code") == 0) {
				p.argsrc = argv[++i];
				continue;
			}

			//Verbosity
			else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
				i++;
				if (argv[i][0] == '0') p.verbosity = 0;
				else if (argv[i][0] == '1') p.verbosity = 1;
				else if (argv[i][0] == '2') p.verbosity = 2;
				else if (argv[i][0] == '3') p.verbosity = 3;
				else {
					std::cout << "\033[1;31mError:\033[0m " << argv[i] << " is not a valid argument to " << argv[i-1] << ".\n";
					p.cont = false;
				}
				continue;
			}

			else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--language") == 0) {
				i++;
				if (strcmp(argv[i], "brainfuck") == 0) p.ilang = I_BF_BRAINFUCK;
				else if (strcmp(argv[i], "tinybf") == 0) p.ilang = I_BF_TINYBF;
				else {
					std::cout << "\033[1;31mError:\033[0m " << argv[i] << " is not a valid input language. Use --list-languages for more info.\n";
					p.cont = false;
				}
				continue;
			}

			else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--target") == 0) {
				i++;
				if (strcmp(argv[i], "c") == 0) p.olang = O_FULL_C;
				else if (strcmp(argv[i], "go") == 0) p.olang = O_FULL_GO;
				else if (strcmp(argv[i], "java") == 0) p.olang = O_FULL_JAVA;
				else if (strcmp(argv[i], "python") == 0) p.olang = O_FULL_PYTHON;

				else if (strcmp(argv[i], "interpreter") == 0) p.olang = O_INTERPRET;

				else if (strcmp(argv[i], "brainfuck") == 0) p.olang = O_BF_BRAINFUCK;
				else {
					std::cout << "\033[1;31mError:\033[0m " << argv[i] << " is not a valid target language. Use --list-languages for more info.\n";
					p.cont = false;
				}
				continue;
			}
		}

		//Deal with arguments without an argument
		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
			p.debug = true;
		}

		else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) { 
			display_help();
			p.cont = false;
		}

		else if (strcmp(argv[i], "--list-languages") == 0) {
			list_languages();
			p.cont = false;
		}

		//If the argument doen't fit, throw error
		else {
			//These arguments need another argument
			if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input-file") == 0) ||
				(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-file") == 0) ||
				(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--error-file") == 0) ||
				(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--code") == 0) ||
				(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--language") == 0) ||
				(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--target") == 0) ) {
				std::cout << "\033[1;31mError:\033[0m " << argv[i] << " requires an argument.\n";
			}

			//Generic error
			else {
				std::cout << "\033[1;31mError:\033[0m " << argv[i] << " is not a valid option.\n";
			}
			p.cont = false;
		}
	}
	return p;
}
