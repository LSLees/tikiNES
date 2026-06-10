#pragma once
#include "../include/common.h"

struct CPU
{
public:
	U8 A = 0; // Accumulator reg
	U8 X = 0; // Index reg
	U8 Y = 0; // Index reg
	U16 PC = 0; // Program counter
	U8 S = 0; // Stack pointer
	U8 P = 0; // Status reg

	void displayReg();
};