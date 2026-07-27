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
	const U8 baseCycles[256] = {
		//  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
			7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6, // 0x0_
			2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, // 0x1_
			6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6, // 0x2_
			2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, // 0x3_
			6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6, // 0x4_
			2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, // 0x5_
			6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6, // 0x6_
			2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, // 0x7_
			2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4, // 0x8_
			2, 6, 2, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5, // 0x9_
			2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4, // 0xA_
			2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4, // 0xB_
			2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6, // 0xC_
			2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, // 0xD_
			2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6, // 0xE_
			2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7, // 0xF_
	};

	U8 A = 0;	// Accumulator reg
	U8 X = 0;	// Index reg
	U8 Y = 0;	// Index reg
	U16 PC = 0;	// Program counter
	U8 S = 0;	// Stack pointer
	U8 P = 0;	// Status reg

	void Reset(NES* nes);
	U8 Step();

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

	// Comparison
	void CMP(U8);
	void CMP_I();
	void CMP_zpg();
	void CMP_abs();
	void CMP_absX();
	void CMP_absY();
	void CMP_zpgX();
};