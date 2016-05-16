#pragma once

#include "datastruct.hpp"
#include "error.hpp"
#include "ir.hpp"
#include <vector>

// These don't make the program faster, but are necessary for
// other optimizations in order to make them actually work
long BFCC_OP_NoOpRemoval(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_JumpRematch(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);

long BFCC_OP_OperationConcatination(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_DeadCodeElimination(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_LazyMoves(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_MultiplyLoopRem(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
long BFCC_OP_ScanLoopRem(BFCC_Parameters&, std::vector<BFCC_Instruction>&, BFCC_Error_Handler&);
