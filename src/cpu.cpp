#include <iostream>
#include "cpu.h"
#include "nes.h"

void CPU::Reset(NES* nes)
{
	this->nes = nes;

	this->PC = nes->Read(0xfffc) | (nes->Read(0xfffd) << 8 ); // Reset vector
	this->S = 0xfd;
	this->P = 0x24;

	// Instruction table
	this->instructions[0xad] = &CPU::LDA_abs;
	this->instructions[0xa9] = &CPU::LDA_I;
	this->instructions[0xa2] = &CPU::LDX_I;
	this->instructions[0xa0] = &CPU::LDY_I;
	this->instructions[0x8d] = &CPU::STA_abs;
	this->instructions[0x9d] = &CPU::STA_absX;
	this->instructions[0x99] = &CPU::STA_absY;
	this->instructions[0xee] = &CPU::INC_abs;
	this->instructions[0xfe] = &CPU::INC_absX;
	this->instructions[0x78] = &CPU::SEI;
	this->instructions[0xd8] = &CPU::CLD;
	this->instructions[0x48] = &CPU::PHA;
	this->instructions[0x68] = &CPU::PLA;
	this->instructions[0x08] = &CPU::PHP;
	this->instructions[0x28] = &CPU::PLP;
	this->instructions[0x20] = &CPU::JSR;
	this->instructions[0x60] = &CPU::RTS;
	this->instructions[0x8a] = &CPU::TXA;
	this->instructions[0x9a] = &CPU::TXS;
	this->instructions[0xaa] = &CPU::TAX;
	this->instructions[0xba] = &CPU::TSX;
	this->instructions[0x10] = &CPU::BPL;
	this->instructions[0xce] = &CPU::DEC_abs;
	this->instructions[0xde] = &CPU::DEC_absX;
}

void CPU::logOp(const char* name)
{
	std::cout << std::hex << "$" << static_cast<int>(PC - 1) << " [0x" << (int)tOpcode << "] - " << name << "\n";
}
void CPU::logOp(const char* name, U8 operand)
{
	std::cout << std::hex << "$" << static_cast<int>(PC - 1) << " [0x" << (int)tOpcode << "] - " << name << " #0x" << (int)operand << "\n";
}
void CPU::logOp(const char* name, U16 operand)
{
	std::cout << std::hex << "$" << static_cast<int>(PC - 2) << " [0x" << (int)tOpcode << "] - " << name << " $" << (int)operand << "\n";
}

void CPU::flagSet(U8 flag)
{
	this->P |= flag;
}

void CPU::flagClear(U8 flag)
{
	this->P &= ~flag;
}

bool CPU::flagRead(U8 flag)
{
	return (this->P & flag);
}

U8 CPU::Fetch8()
{
	return this->nes->Read(this->PC++);
}

U16 CPU::Fetch16()
{
	U8 lo = Fetch8();
	U8 hi = Fetch8();
	return lo | (hi << 8);
}

void CPU::stackPush(U8 data)
{
	nes->Write(0x0100 | this->S, data);
	this->S--;
}

U8 CPU::stackPull()
{
	this->S++;
	return nes->Read(0x0100 | this->S);
}

void CPU::Step()
{
	U8 opcode = Fetch8();
	tOpcode = opcode;

	if (instructions[opcode] == nullptr)
	{
		nes->running = false;
		return;
	}

	(this->*instructions[opcode])();
}

void CPU::LDA_abs()
{
	U16 operand = Fetch16();
	logOp("LDA_abs ", operand);
	A = nes->Read(operand);
	this->A == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->A & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::LDA_I()
{
	U8 operand = Fetch8();
	logOp("LDA_I   ", operand);
	this->A = operand;
	this->A == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->A & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::LDX_I()
{
	U8 operand = Fetch8();
	logOp("LDX_I   ", operand);
	this->X = operand;
	this->X == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->X & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::LDY_I()
{
	U8 operand = Fetch8();
	logOp("LDY_I   ", operand);
	this->Y = operand;
	this->Y == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->Y & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::STA_abs()
{
	U16 operand = Fetch16();
	logOp("STA_abs ", operand);
	this->nes->Write(operand, this->A);
}

void CPU::STA_absX()
{
	U16 operand = Fetch16();
	logOp("STA_absX", operand);
	this->nes->Write(operand + this->X, this->A);
}

void CPU::STA_absY()
{
	U16 operand = Fetch16();
	logOp("STA_absY", operand);
	this->nes->Write(operand + this->Y, this->A);
}

void CPU::INC_abs()
{
	U16 operand = Fetch16();
	logOp("INC_abs ", operand);
	U8 data = this->nes->Read(operand) + 1;
	this->nes->Write(operand, data);
	data == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	data & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::INC_absX()
{
	U16 operand = Fetch16() + this->X;
	logOp("INC_absX", operand);
	U8 data = this->nes->Read(operand) + 1;
	this->nes->Write(operand, data);
	data == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	data & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::SEI()
{
	logOp("SEI");
	flagSet(flag_I);
}

void CPU::CLD() // Probably doesnt need anything
{
	logOp("CLD");
}

void CPU::PHA()
{
	logOp("PHA");
	stackPush(this->A);
}

void CPU::PLA()
{
	logOp("PLA     ");
	this->A = stackPull();
	this->A == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->A & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::PHP()
{
	logOp("PHP");
	stackPush(this->P | 0x30); // Bit 5 and break should be high ??
	flagSet(flag_B);
}

void CPU::PLP()
{
	logOp("PLP");
	this->P = stackPull() & ~0x10;
}

void CPU::JSR()
{
	U16 operand = Fetch16();
	logOp("JSR     ", operand);
	U16 ret = this->PC - 1;
	stackPush((ret >> 8) & 0xff); // Store return address
	stackPush(ret & 0xff);
	this->PC = operand;
}

void CPU::RTS()
{
	logOp("RTS");
	U8 lo = stackPull(); // Retrieve return address
	U8 hi = stackPull();
	this->PC = (lo | (hi << 8)) + 1;
}

void CPU::TXA()
{
	logOp("TXA");
	A = X;
	this->A == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->A & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::TXS()
{
	logOp("TXS");
	S = X;
}

void CPU::TAX()
{
	logOp("TAX");
	X = A;
	this->X == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->X & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::TSX()
{
	logOp("TSX");
	X = S;
	this->X == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->X & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::BPL()
{
	S8 operand = static_cast<int8_t>(Fetch8());
	logOp("BPL     ", static_cast<U8>(operand));

	if (!flagRead(flag_N))
	{
		PC += operand;
	}
}

void CPU::DEC_abs()
{
	U16 operand = Fetch16();
	logOp("DEC_abs ", operand);
	U8 data = this->nes->Read(operand) - 1;
	this->nes->Write(operand, data);
	data == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	data & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::DEC_absX()
{
	U16 operand = Fetch16() + this->X;
	logOp("DEC_absX", operand);
	U8 data = this->nes->Read(operand) - 1;
	this->nes->Write(operand, data);
	data == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	data & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}