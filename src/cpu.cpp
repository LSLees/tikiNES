#include <iostream>
#include "cpu.h"
#include "nes.h"

void CPU::Reset(NES* nes)
{
	this->nes = nes;

	this->PC = 0; // find entry point?
	this->S = 0xfd;
	this->P = 0x24;

	// Init instruction table
	this->instructions[0xa9] = &CPU::LDA_I;
	this->instructions[0xa2] = &CPU::LDX_I;
	this->instructions[0xa0] = &CPU::LDY_I;
	this->instructions[0x8d] = &CPU::STA_abs;
	this->instructions[0x9d] = &CPU::STA_absX;
	this->instructions[0x99] = &CPU::STA_absY;
	this->instructions[0xee] = &CPU::INC_abs;
	this->instructions[0xfe] = &CPU::INC_absX;
}

void CPU::displayReg()
{
	std::cout << " A: " << static_cast<U16>(this->A) << std::endl;
	std::cout << " X: " << static_cast<U16>(this->X) << std::endl;
	std::cout << " Y: " << static_cast<U16>(this->Y) << std::endl;
	std::cout << "PC: " << static_cast<U16>(this->PC) << std::endl;
	std::cout << " S: " << static_cast<U16>(this->S) << std::endl;
	std::cout << " P: " << static_cast<U16>(this->P) << std::endl;
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
	return this->nes->wram.Read(this->PC++);
}

U16 CPU::Fetch16()
{
	U8 lo = Fetch8();
	U8 hi = Fetch8();
	return lo | (hi << 8);
}

void CPU::Step()
{
	U8 opcode = Fetch8();

	if (instructions[opcode] == nullptr)
	{
		std::cout << "Opcode: " << opcode << " not defined!" << std::endl;
		return;
	}

	std::cout << "Executing: " << (int)opcode << std::endl;
	(this->*instructions[opcode])();
}

void CPU::LDA_I() // Load A, immediate
{
	this->A = Fetch8();
	this->A == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->A & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::LDX_I() // Load X, immediate
{
	this->X = Fetch8();
	this->X == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->X & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::LDY_I() // Load Y, immediate
{
	this->Y = Fetch8();
	this->Y == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	this->Y & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::STA_abs() // Store absolute, A
{
	this->nes->wram.Write(Fetch16(), this->A);
}

void CPU::STA_absX() // Store absolute + X, A
{
	this->nes->wram.Write(Fetch16() + this->X, this->A);
}

void CPU::STA_absY() // Store absolute + Y, A
{
	this->nes->wram.Write(Fetch16() + this->Y, this->A);
}

void CPU::INC_abs() // Increment absolute
{
	U16 address = Fetch16();
	U8 data = this->nes->wram.Read(address) + 1;
	this->nes->wram.Write(address, data);
	data == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	data & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}

void CPU::INC_absX() // Increment absolute + X
{
	U16 address = Fetch16() + this->X;
	U8 data = this->nes->wram.Read(address) + 1;
	this->nes->wram.Write(address, data);
	data == 0 ? flagSet(flag_Z) : flagClear(flag_Z);
	data & 0x80 ? flagSet(flag_N) : flagClear(flag_N);
}