#pragma once

#include <vector>
#include <memory>
#include "../ast.hpp"
#include "../visitors.hpp"

class BFCC_Optimizer : public BFCC_Visitor {
protected:
	std::vector<std::shared_ptr<BFCC_Node>> output;
public:
	std::vector<std::shared_ptr<BFCC_Node>> get_nodes();
};