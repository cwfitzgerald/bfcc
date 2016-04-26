#include <iostream>
#include "ast.hpp"

void BFCC_Node::set_data(long sline, long schar, long eline, long echar) {
	loc.startline = sline;
	loc.startchar = schar;
	loc.endline   = eline;
	loc.endchar   = echar;
}

BFCC_Node_DPTRmv::BFCC_Node_DPTRmv (long icount) {
	count = icount;
}

void BFCC_Node_DPTRmv::accept(BFCC_Visitor * v) {
	v->visit(this);
}

long BFCC_Node_DPTRmv::get_count() {
	return count;
}


BFCC_Node_DATAadd::BFCC_Node_DATAadd (long icount) {
	count = icount;
}

void BFCC_Node_DATAadd::accept(BFCC_Visitor * v) {
	v->visit(this);
}


long BFCC_Node_DATAadd::get_count() {
	return count;
}


BFCC_Node_DATAprint::BFCC_Node_DATAprint (long icount) {
	count = icount;
}

void BFCC_Node_DATAprint::accept(BFCC_Visitor * v) {
	v->visit(this);
}

long BFCC_Node_DATAprint::get_count() {
	return count;
}


BFCC_Node_DATAget::BFCC_Node_DATAget (long icount) {
	count = icount;
}

void BFCC_Node_DATAget::accept(BFCC_Visitor * v) {
	v->visit(this);
}

long BFCC_Node_DATAget::get_count() {
	return count;
}


void BFCC_Node_CTRLLoop::subaccept (BFCC_Visitor * vptr) {
	for (auto n : subnodes) {
		n->accept(vptr);
	}
}

void BFCC_Node_CTRLLoop::add(std::shared_ptr<BFCC_Node> n) {
	subnodes.push_back(n);
}

void BFCC_Node_CTRLLoop::accept(BFCC_Visitor * v) {
	v->visit(this);
}
