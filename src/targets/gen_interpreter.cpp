#include <string>
#include <memory>
#include <cinttypes>
#include <iostream>
#include "targets.hpp"

std::string BFCC_Target_Interpreter::gen_target() {
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
				std::cin >> data[dptr];
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

void BFCC_Target_Interpreter::visit (std::shared_ptr<BFCC_Node_DPTRmv> n) {
	ilist.push_back({DPTRMV, n->get_count()});
	curinstrnum++;
}

void BFCC_Target_Interpreter::visit (std::shared_ptr<BFCC_Node_DATAadd> n) {
	ilist.push_back({DADD, n->get_count()});
	curinstrnum++;
}

void BFCC_Target_Interpreter::visit (std::shared_ptr<BFCC_Node_DATAprint> n) {
	ilist.push_back({DPRINT, n->get_count()});
	curinstrnum++;
}

void BFCC_Target_Interpreter::visit (std::shared_ptr<BFCC_Node_DATAget> n) {
	ilist.push_back({DGET, n->get_count()});
	curinstrnum++;
}

void BFCC_Target_Interpreter::visit (std::shared_ptr<BFCC_Node_CTRLLoop> n) {
	ilist.push_back({JZ, 0});
	long start = curinstrnum++;
	n->subaccept(this);
	ilist[start].data1 = curinstrnum++;
	ilist.push_back({JNZ, start});
}
