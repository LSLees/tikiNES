#pragma once
#include "../include/common.h"

#define flag_C 0x01
#define flag_Z 0x02
#define flag_I 0x04
#define flag_D 0x80
#define flag_B 0x10
#define flag_V 0x40
#define flag_N 0x80

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
	void flagSet(U8 flag);
	void flagClear(U8 flag);
	bool flagRead(U8 flag);
};