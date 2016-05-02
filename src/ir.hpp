#pragma once

#include "ast.hpp"
#include "visitors.hpp"
#include "error.hpp"
#include <string>
#include <memory>

enum BFCC_Bytecode {
	DPTRMV, DADD, DPRINT, DGET, JZ, JNZ
};

struct BFCC_Instruction {
	BFCC_Bytecode type;
	long data1 = 0;
	long data2 = 0;
	long data3 = 0;
};

class BFCC_AST_to_IR : public BFCC_Visitor {
private:
	BFCC_Parameters params;
	BFCC_Error_Handler errhdlr;

	long curinstrnum = 0;

	std::vector<BFCC_Instruction> ilist;

public:
	BFCC_AST_to_IR(BFCC_Parameters& p, BFCC_Error_Handler& e) : params(p), errhdlr(e) {}
	std::vector<BFCC_Instruction> generate (std::vector<std::shared_ptr<BFCC_Node>> v);

	void visit (std::shared_ptr<BFCC_Node_DPTRmv>        n);
	void visit (std::shared_ptr<BFCC_Node_DATAadd>       n);
	void visit (std::shared_ptr<BFCC_Node_DATAprint>     n);
	void visit (std::shared_ptr<BFCC_Node_DATAget>       n);
	void visit (std::shared_ptr<BFCC_Node_CTRLLoop>      n);
};