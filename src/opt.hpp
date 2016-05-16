#pragma once

#include "error.hpp"
#include "ir.hpp"
#include <vector>

long BFCC_OP_OperationConcatination(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_NoOpRemoval(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_JumpRematch(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_DeadCodeElimination(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_LazyMoves(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_MultiplyLoopRem(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_ScanLoopRem(std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
