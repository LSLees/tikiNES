#pragma once
#include <stdint.h>

struct CPU
{
public:
	uint8_t A = 0; // Accumulator reg
	uint8_t X = 0; // Index reg
	uint8_t Y = 0; // Index reg
	uint16_t PC = 0; // Program counter
	uint8_t S = 0; // Stack pointer
	uint8_t P = 0; // Status reg

	void displayReg();
};