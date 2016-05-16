#pragma once

#include "../datastruct.hpp"
#include "../error.hpp"
#include "../ir.hpp"
#include <memory>
#include <string>
#include <vector>

class BFCC_Target {
  protected:
	std::string endsrc;
	BFCC_Parameters params;
	BFCC_Error_Handler* errhdlr;

  public:
	BFCC_Target(BFCC_Parameters& p, BFCC_Error_Handler& e)
	  : params(p)
	  , errhdlr(&e){};
	virtual std::string generate(std::vector<BFCC_Instruction>) = 0;
};

class BFCC_Target_Brainfuck : public BFCC_Target {
  public:
	BFCC_Target_Brainfuck(BFCC_Parameters& p, BFCC_Error_Handler& e)
	  : BFCC_Target(p, e)
	{
	}
	std::string generate(std::vector<BFCC_Instruction>);
};

class BFCC_Target_Interpreter : public BFCC_Target {
  public:
	BFCC_Target_Interpreter(BFCC_Parameters& p, BFCC_Error_Handler& e)
	  : BFCC_Target(p, e)
	{
	}
	std::string generate(std::vector<BFCC_Instruction>);
};
