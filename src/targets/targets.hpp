#pragma once

#include <string>
#include <memory>
#include <vector>
#include "../ast.hpp"
#include "../datastruct.hpp"
#include "../error.hpp"
#include "../visitors.hpp"

class BFCC_Target : public BFCC_Visitor {
protected:
	std::string endsrc;
	BFCC_Parameters params;
	BFCC_Error_Handler err;
public:
	BFCC_Target(BFCC_Parameters& p, BFCC_Error_Handler& e) {
		params = p;
		err = e;
	};
	virtual std::string gen_target() = 0;
};

class BFCC_Target_Brainfuck : public BFCC_Target {
public:
	BFCC_Target_Brainfuck(BFCC_Parameters& p, BFCC_Error_Handler& e) : BFCC_Target(p,e) {}
	std::string gen_target();

	void visit (std::shared_ptr<BFCC_Node_DPTRmv>        n);
	void visit (std::shared_ptr<BFCC_Node_DATAadd>       n);
	void visit (std::shared_ptr<BFCC_Node_DATAprint>     n);
	void visit (std::shared_ptr<BFCC_Node_DATAget>       n);
	void visit (std::shared_ptr<BFCC_Node_CTRLLoop>      n);
};

class BFCC_Target_Interpreter : public BFCC_Target {
private:
	enum bytecode {
		DPTRMV, DADD, DPRINT, DGET, JZ, JNZ
	};
	struct instruction {
		bytecode type;
		long data1 = 0;
		long data2 = 0;
		long data3 = 0;
	};

	std::vector<instruction> ilist;

	long curinstrnum = 0;

public:
	BFCC_Target_Interpreter(BFCC_Parameters& p, BFCC_Error_Handler& e) : BFCC_Target(p,e) {}
	std::string gen_target();

	void visit (std::shared_ptr<BFCC_Node_DPTRmv>        n);
	void visit (std::shared_ptr<BFCC_Node_DATAadd>       n);
	void visit (std::shared_ptr<BFCC_Node_DATAprint>     n);
	void visit (std::shared_ptr<BFCC_Node_DATAget>       n);
	void visit (std::shared_ptr<BFCC_Node_CTRLLoop>      n);
};
