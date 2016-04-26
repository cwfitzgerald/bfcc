#include <string>
#include <cmath>
#include <iostream>
#include "targets.hpp"

void BFCC_Target_Brainfuck::visit (BFCC_Node_DPTRmv*    n) {
	char c = '>';
	if (n->get_count() < 0)
		c = '<';

	for (int i = 0; i < abs(n->get_count()); i++) {
		endsrc += c;
	}
};

void BFCC_Target_Brainfuck::visit (BFCC_Node_DATAadd*   n) {
	char c = '+';
	if (n->get_count() < 0)
		c = '-';

	for (int i = 0; i < abs(n->get_count()); i++) {
		endsrc += c;
	}
};

void BFCC_Target_Brainfuck::visit (BFCC_Node_DATAprint* n) {
	for (int i = 0; i < n->get_count(); i++){
		endsrc += '.';
	}
};

void BFCC_Target_Brainfuck::visit (BFCC_Node_DATAget*   n) {
	for (int i = 0; i < n->get_count(); i++){
		endsrc += ',';
	}
};

void BFCC_Target_Brainfuck::visit (BFCC_Node_CTRLLoop*  n) {
	endsrc += '[';
	n->subaccept(this);
	endsrc += ']';
};
