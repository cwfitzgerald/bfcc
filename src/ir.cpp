#include "ast.hpp"
#include "ir.hpp"
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>

std::vector<BFCC_Instruction> BFCC_AST_to_IR::generate (std::vector<std::shared_ptr<BFCC_Node>> nodelist) {
	for (auto i : nodelist) {
		i->accept(this);
	}

	ilist.push_back({END});

	return ilist;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DPTRmv> n) {
	ilist.push_back({DPTRMV, n->get_count(), 0, 0, n->get_data().startline, n->get_data().startchar});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DATAadd> n) {
	ilist.push_back({DADD, n->get_count(), 0, 0, n->get_data().startline, n->get_data().startchar});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DATAprint> n) {
	ilist.push_back({DPRINT, n->get_count(), 0, 0, n->get_data().startline, n->get_data().startchar});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DATAget> n) {
	ilist.push_back({DGET, n->get_count(), 0, 0, n->get_data().startline, n->get_data().startchar});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_CTRLLoop> n) {
	ilist.push_back({JZ, 0, 0, 0, n->get_data().startline, n->get_data().startchar});
	long start = curinstrnum++;
	n->subaccept(this);
	ilist[start].data1 = curinstrnum++;
	ilist.push_back({JNZ, start, 0, 0, n->get_data().endline, n->get_data().endchar});
}

std::string BFCC_IR_PPrint(std::vector<BFCC_Instruction> oplist) {
	std::ostringstream out;

	int maxnumwidth = std::ceil(std::log10(oplist.size())); 
	
	out << "Num:   Name\tLong Name \t   Data \tOffset\n";

	int curpos = 0;
	for (auto op : oplist) {
		out << " " << std::setfill('0') << std::setw(maxnumwidth) << curpos << ":   ";
		switch (op.type) {
			case DPTRMV:
				out << "DPTRMV\tMOVE_DATA_POINTER    " << op.data1 << "\t\t" << op.offset;
				break;

			case DADD:
				out << "DADD\tDATA_ADD\t     " << op.data1 << "\t\t" << op.offset;
				break;

			case DPRINT:
				out << "DPRINT\tDATA_PRINT\t     " << op.data1 << "\t\t" << op.offset;
				break;

			case DGET:
				out << "DGET\tDATA_GET\t     " << op.data1 << "\t\t" << op.offset;
				break;

			case JZ:
				out << "JZ\tJUMP_IF_ZERO\t     " << op.data1 << "\t\t-";
				break;

			case JNZ:
				out << "JNZ\tJUMP_NOT_ZERO\t     " << op.data1 << "\t\t-";
				break;

			case DDCALC:
				out << "DDCALC\tDATA_DENOM_CALC\t     " << op.data1 << "\t\t" << op.offset;
				break;

			case DMUL:
				out << "DMUL\tDATA_MULTIPLY\t     " << op.data1 << ", " << op.data2 << "\t" << op.offset;
				break;

			case NOP:
				out << "NOP\tNO_OPERATION\t     \t\tDo nothing";
				break;

			case END:
				out << "END\tEND_PROGRAM\t     \t\tEnd the program";
				break; 
		}
		curpos++;
		out << "\n";
	}
	out << "--------------------------------\n";

	return out.str();
}
