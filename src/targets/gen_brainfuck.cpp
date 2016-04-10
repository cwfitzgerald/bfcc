#include <string>
#include <iostream>
#include "targets.hpp"

void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWAdd*      n) { endsrc += '+'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWSub*      n) { endsrc += '-'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWLeft*     n) { endsrc += '<'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWRight*    n) { endsrc += '>'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWLeftbrk*  n) { endsrc += '['; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWRightbrk* n) { endsrc += ']'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWDot*      n) { endsrc += '.'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_RAWComma*    n) { endsrc += ','; (void) n;  };