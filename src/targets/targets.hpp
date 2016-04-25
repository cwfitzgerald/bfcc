#pragma once

#include <string>
#include "../ast.hpp"
#include "../visitors.hpp"

class BFCC_Target : public BFCC_Visitor {
protected:
	std::string endsrc;
public:
	std::string gen_target() {
		return endsrc;
	};
};

class BFCC_Target_Brainfuck : public BFCC_Target {
public:
	void visit (BFCC_Node_DPTRmv*        n);
	void visit (BFCC_Node_DATAadd*       n);
	void visit (BFCC_Node_DATAprint*     n);
	void visit (BFCC_Node_DATAget*       n);
	void visit (BFCC_Node_CTRLLoop*      n);
};