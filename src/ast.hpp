#pragma once

#include <memory>
#include <iosfwd>
#include "astfwd.hpp"
#include "visitors.hpp"
#include "datastruct.hpp"

struct LocationInfo {
	long startline;
	long startchar;
	long endline;
	long endchar;
};

class BFCC_Node {
private:
	LocationInfo loc;
public:
	void set_data(long sline, long schar, long eline, long echar);
	virtual void accept(std::shared_ptr<BFCC_Visitor>) = 0;
};

class BFCC_Node_PTRmv       : public BFCC_Node {
	void accept(std::shared_ptr<BFCC_Visitor>);
};

class BFCC_Node_DATAadd     : public BFCC_Node {
	void accept(std::shared_ptr<BFCC_Visitor>);
};

class BFCC_Node_DATAprint   : public BFCC_Node {
	void accept(std::shared_ptr<BFCC_Visitor>);
};

class BFCC_Node_DATAget     : public BFCC_Node {
	void accept(std::shared_ptr<BFCC_Visitor>);
};

class BFCC_Node_CTRLLoop    : public BFCC_Node {
	void accept(std::shared_ptr<BFCC_Visitor>);
};