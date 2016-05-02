#include "ast.hpp"
#include "ir.hpp"
#include <string>
#include <memory>
#include <vector>

std::vector<BFCC_Instruction> BFCC_AST_to_IR::generate (std::vector<std::shared_ptr<BFCC_Node>> nodelist) {
	for (auto i : nodelist) {
		i->accept(this);
	}

	return ilist;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DPTRmv> n) {
	ilist.push_back({DPTRMV, n->get_count()});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DATAadd> n) {
	ilist.push_back({DADD, n->get_count()});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DATAprint> n) {
	ilist.push_back({DPRINT, n->get_count()});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_DATAget> n) {
	ilist.push_back({DGET, n->get_count()});
	curinstrnum++;
}

void BFCC_AST_to_IR::visit (std::shared_ptr<BFCC_Node_CTRLLoop> n) {
	ilist.push_back({JZ, 0});
	long start = curinstrnum++;
	n->subaccept(this);
	ilist[start].data1 = curinstrnum++;
	ilist.push_back({JNZ, start});
}
