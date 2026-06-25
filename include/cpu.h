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

	void Reset(NES* nes);
	void Step();

	// Logging
	void logOp(const char* name);
	void logOp(const char* name, U8 operand);
	void logOp(const char* name, U16 operand);
	U8 tOpcode = 0;

	// Flags
	void flagSet(U8 flag);
	void flagClear(U8 flag);
	bool flagRead(U8 flag);

	U8 Fetch8();
	U16 Fetch16();
	void stackPush(U8 data);
	U8 stackPull();

	// Instructions
	void (CPU::* instructions[256])() = { 0 };

	// Load
	void LDA_abs(); // Load A, [imm]
	void LDA_I(); // Load A, imm
	void LDX_I(); // Load X, imm
	void LDY_I(); // Load Y, imm

	// Store
	void STA_abs(); // Store abs, A
	void STA_absX(); // Store abs + X, A
	void STA_absY(); // Store abs + Y, A

	// Increment
	void INC_abs(); // Inc abs
	void INC_absX(); // Inc abs + X

	// Flags
	void SEI(); // Set interrupts
	void CLD(); // Clear decimal

	// Stack
	void PHA(); // Push A
	void PLA(); // Pull A
	void PHP(); // Push P
	void PLP(); // Pull P

	// Jump
	void JSR(); // Jump to subroutine
	void RTS(); // Return from subroutine

	// Transfer
	void TXA();
	void TXS();
	void TAX();
	void TSX();

	// Branch
	void BPL();

	// Decrement
	void DEC_abs();
	void DEC_absX();
};