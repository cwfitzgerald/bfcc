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
	void visit (BFCC_Node_RAWAdd*      n);
	void visit (BFCC_Node_RAWSub*      n);
	void visit (BFCC_Node_RAWLeft*     n);
	void visit (BFCC_Node_RAWRight*    n);
	void visit (BFCC_Node_RAWLeftbrk*  n);
	void visit (BFCC_Node_RAWRightbrk* n);
	void visit (BFCC_Node_RAWDot*      n);
	void visit (BFCC_Node_RAWComma*    n);
};