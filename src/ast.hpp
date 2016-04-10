#pragma once

#include <memory>
#include <vector>
#include "datastruct.hpp"

class BFCC_AST_Node {
public:
	virtual void compute(BFCC_Data dt) = 0;
};