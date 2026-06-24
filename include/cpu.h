#pragma once
#include "common.h"

#define flag_C 0x01	// Carry
#define flag_Z 0x02 // Zero
#define flag_I 0x04	// Interrupts disabled
#define flag_B 0x10	// Break
#define flag_V 0x40	// Overflow
#define flag_N 0x80	// Negative

struct NES;

struct CPU
{
	NES* nes = nullptr;

	U8 A = 0;	// Accumulator reg
	U8 X = 0;	// Index reg
	U8 Y = 0;	// Index reg
	U16 PC = 0;	// Program counter
	U8 S = 0;	// Stack pointer
	U8 P = 0;	// Status reg

	void printPC();

	void flagSet(U8 flag);
	void flagClear(U8 flag);
	bool flagRead(U8 flag);

	void Reset(NES* nes);
	U8 Fetch8();
	U16 Fetch16();
	void Step();

	// Instructions
	void (CPU::* instructions[256])() = { 0 };
	void LDA_I();
	void LDX_I();
	void LDY_I();
	void STA_abs();
	void STA_absX();
	void STA_absY();
	void INC_abs();
	void INC_absX();
	void SEI();
	void CLD();
};