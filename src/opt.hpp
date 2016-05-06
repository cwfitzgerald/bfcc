#pragma once

#include "ir.hpp"
#include <vector>

long BFCC_OP_OperationConcatination (std::vector<BFCC_Instruction>&);
long BFCC_OP_NoOpRemoval (std::vector<BFCC_Instruction>&);
long BFCC_OP_JumpRematch (std::vector<BFCC_Instruction>&);
long BFCC_OP_DeadCodeElimination (std::vector<BFCC_Instruction>&);
long BFCC_OP_ClearLoopRem (std::vector<BFCC_Instruction>&);
long BFCC_OP_MultiplyLoopRem (std::vector<BFCC_Instruction>&);
long BFCC_OP_LazyMoves (std::vector<BFCC_Instruction>&);
