#pragma once

#include "astfwd.hpp"
#include "datastruct.hpp"
#include "visitors.hpp"
#include <iosfwd>
#include <memory>

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
	LocationInfo get_data();
	virtual void accept(BFCC_Visitor*) = 0;
};

class BFCC_Node_DPTRmv : public BFCC_Node, public std::enable_shared_from_this<BFCC_Node_DPTRmv> {
  private:
	long count;

  public:
	BFCC_Node_DPTRmv(long icount = 1);
	long get_count();
	void accept(BFCC_Visitor*);
};

class BFCC_Node_DATAadd : public BFCC_Node, public std::enable_shared_from_this<BFCC_Node_DATAadd> {
  private:
	long count;

  public:
	BFCC_Node_DATAadd(long icount = 1);
	long get_count();
	void accept(BFCC_Visitor*);
};

class BFCC_Node_DATAprint : public BFCC_Node, public std::enable_shared_from_this<BFCC_Node_DATAprint> {
  private:
	long count;

  public:
	BFCC_Node_DATAprint(long icount = 1);
	long get_count();
	void accept(BFCC_Visitor*);
};

class BFCC_Node_DATAget : public BFCC_Node, public std::enable_shared_from_this<BFCC_Node_DATAget> {
  private:
	long count;

  public:
	BFCC_Node_DATAget(long icount = 1);
	long get_count();
	void accept(BFCC_Visitor*);
};

class BFCC_Node_CTRLLoop : public BFCC_Node, public std::enable_shared_from_this<BFCC_Node_CTRLLoop> {
  private:
	std::vector<std::shared_ptr<BFCC_Node>> subnodes;

  public:
	void subaccept(BFCC_Visitor*);
	void add(std::shared_ptr<BFCC_Node>);
	void accept(BFCC_Visitor*);
};
