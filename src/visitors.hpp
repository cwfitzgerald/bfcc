#pragma once

#include "astfwd.hpp"
#include "ast.hpp"

class BFCC_Visitor {
public:
	virtual void visit (BFCC_Node_PTRmv*         n) = 0;
	virtual void visit (BFCC_Node_DATAadd*       n) = 0;
	virtual void visit (BFCC_Node_DATAprint*     n) = 0;
	virtual void visit (BFCC_Node_DATAget*       n) = 0;
	virtual void visit (BFCC_Node_CTRLLoop*      n) = 0;
};