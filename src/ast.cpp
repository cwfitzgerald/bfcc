#include <memory>
#include <iostream>
#include "ast.hpp"

void BFCC_Node::set_data(long sline, long schar, long eline, long echar) {
	loc.startline = sline;
	loc.startchar = schar;
	loc.endline   = eline;
	loc.endchar   = echar;
}

void BFCC_Node_PTRmv::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}

void BFCC_Node_DATAadd::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}

void BFCC_Node_DATAprint::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}

void BFCC_Node_DATAget::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}

void BFCC_Node_CTRLLoop::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
