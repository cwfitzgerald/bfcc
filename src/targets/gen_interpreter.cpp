#include <string>
#include <cinttypes>
#include "targets.hpp"
#include "../ir.hpp"

std::string BFCC_Target_Interpreter::generate(std::vector<BFCC_Instruction> ilist) {
	std::vector<uint8_t> data (32768, 0);
	unsigned long dptr = 0;

	auto checkptr = [&dptr]() {
		dptr &= 32767;
	};

	for (long iptr = 0; iptr < ilist.size(); iptr++) {
		//std::cout << iptr << "\n";
		switch (ilist[iptr].type) {
			case DPTRMV:
				dptr += ilist[iptr].data1;
				checkptr();
				break;

			case DADD:
				data[dptr] += ilist[iptr].data1;
				break;

			case DPRINT:
				for (int i = 0; i < ilist[iptr].data1; i++) {
					params.out->put(static_cast<char>(data[dptr]));
				}
				break;

			case DGET:
				if (ilist[iptr].data1 > 1) {
					std::cin.ignore(ilist[iptr].data1 - 1);
				}

				char c;
				if (std::cin.get(c)) {
					data[dptr] = static_cast<uint8_t>(c);
				}
				else {
					data[dptr] = 0;
				}
				
				break;

			case JZ:
				if (data[dptr] == 0) {
					iptr = ilist[iptr].data1;
				}
				break;

			case JNZ:
				if (data[dptr] != 0) {
					iptr = ilist[iptr].data1;
				}
				break;
		}
	}

	return "";
}
