#pragma once

#include "astfwd.hpp"
#include "ast.hpp"

class BFCC_Visitor {
public:
	virtual void visit (BFCC_Node_RAWAdd*      n) = 0;
	virtual void visit (BFCC_Node_RAWSub*      n) = 0;
	virtual void visit (BFCC_Node_RAWLeft*     n) = 0;
	virtual void visit (BFCC_Node_RAWRight*    n) = 0;
	virtual void visit (BFCC_Node_RAWLeftbrk*  n) = 0;
	virtual void visit (BFCC_Node_RAWRightbrk* n) = 0;
	virtual void visit (BFCC_Node_RAWDot*      n) = 0;
	virtual void visit (BFCC_Node_RAWComma*    n) = 0;
};