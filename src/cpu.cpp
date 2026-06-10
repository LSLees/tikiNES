#include "../include/cpu.h"
#include <iostream>

void CPU::displayReg()
{
	std::cout << "A: " << static_cast<U16>(this->A) << std::endl;
	std::cout << "X: " << static_cast<U16>(this->X) << std::endl;
	std::cout << "Y: " << static_cast<U16>(this->Y) << std::endl;
	std::cout << "C: " << static_cast<U16>(this->PC) << std::endl;
	std::cout << "S: " << static_cast<U16>(this->S) << std::endl;
	std::cout << "P: " << static_cast<U16>(this->P) << std::endl;
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