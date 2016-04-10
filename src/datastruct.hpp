#pragma once

#include <vector>
#include <cinttypes>

class BFCC_Data {
	std::vector<uint8_t> tape;
	long ptr = 0;
};