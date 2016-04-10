#include <memory>
#include <iostream>
#include "ast.hpp"

void BFCC_Node::set_data(long sline, long schar, long eline, long echar) {
	loc.startline = sline;
	loc.startchar = schar;
	loc.endline   = eline;
	loc.endchar   = echar;
}

void BFCC_Node_RAWAdd::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWSub::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWLeft::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWRight::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWLeftbrk::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWRightbrk::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWDot::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
void BFCC_Node_RAWComma::accept(std::shared_ptr<BFCC_Visitor> v) {
	v->visit(this);
}
