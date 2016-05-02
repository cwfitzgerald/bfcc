#pragma once

#include "astfwd.hpp"
#include "ast.hpp"
#include <memory>

class BFCC_Visitor {
public:
	virtual void visit (std::shared_ptr<BFCC_Node_DPTRmv>        n) = 0;
	virtual void visit (std::shared_ptr<BFCC_Node_DATAadd>       n) = 0;
	virtual void visit (std::shared_ptr<BFCC_Node_DATAprint>     n) = 0;
	virtual void visit (std::shared_ptr<BFCC_Node_DATAget>       n) = 0;
	virtual void visit (std::shared_ptr<BFCC_Node_CTRLLoop>      n) = 0;
};
