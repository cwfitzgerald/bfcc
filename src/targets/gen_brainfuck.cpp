#include <string>
#include <iostream>
#include "targets.hpp"

void BFCC_Target_Brainfuck::visit (BFCC_Node_PTRmv*     n) { endsrc += '+'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_DATAadd*   n) { endsrc += '-'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_DATAprint* n) { endsrc += '<'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_DATAget*   n) { endsrc += '>'; (void) n;  };
void BFCC_Target_Brainfuck::visit (BFCC_Node_CTRLLoop*  n) { endsrc += '['; (void) n;  };
