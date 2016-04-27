#include <cstdlib>
#include <memory>
#include <string>
#include "targets.hpp"

std::string BFCC_Target_Brainfuck::gen_target() {
	return endsrc;
}

void BFCC_Target_Brainfuck::visit (std::shared_ptr<BFCC_Node_DPTRmv>    n) {
	char c = '>';
	if (n->get_count() < 0)
		c = '<';

	for (int i = 0; i < labs(n->get_count()); i++) {
		endsrc += c;
	}
};

void BFCC_Target_Brainfuck::visit (std::shared_ptr<BFCC_Node_DATAadd>   n) {
	char c = '+';
	if (n->get_count() < 0)
		c = '-';

	for (int i = 0; i < labs(n->get_count()); i++) {
		endsrc += c;
	}
};

void BFCC_Target_Brainfuck::visit (std::shared_ptr<BFCC_Node_DATAprint> n) {
	for (int i = 0; i < n->get_count(); i++){
		endsrc += '.';
	}
};

void BFCC_Target_Brainfuck::visit (std::shared_ptr<BFCC_Node_DATAget>   n) {
	for (int i = 0; i < n->get_count(); i++){
		endsrc += ',';
	}
};

void BFCC_Target_Brainfuck::visit (std::shared_ptr<BFCC_Node_CTRLLoop>  n) {
	endsrc += '[';
	n->subaccept(this);
	endsrc += ']';
};
