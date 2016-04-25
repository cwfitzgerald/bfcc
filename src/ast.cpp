#include <memory>
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

void BFCC_Node_DPTRmv::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}


BFCC_Node_DATAadd::BFCC_Node_DATAadd (long icount) {
	count = icount;
}

void BFCC_Node_DATAadd::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}


BFCC_Node_DATAprint::BFCC_Node_DATAprint (long icount) {
	count = icount;
}

void BFCC_Node_DATAprint::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}


BFCC_Node_DATAget::BFCC_Node_DATAget (long icount) {
	count = icount;
}

void BFCC_Node_DATAget::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}


void BFCC_Node_CTRLLoop::add(std::shared_ptr<BFCC_Node> n) {
	subnodes.push_back(n);
}

void BFCC_Node_CTRLLoop::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
