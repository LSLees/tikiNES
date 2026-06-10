#include "../include/cpu.h"
#include <iostream>

void CPU::displayReg()
{
	std::cout << "A: " << static_cast<uint16_t>(this->A) << std::endl;
	std::cout << "X: " << static_cast<uint16_t>(this->X) << std::endl;
	std::cout << "Y: " << static_cast<uint16_t>(this->Y) << std::endl;
	std::cout << "PC: " << static_cast<uint16_t>(this->PC) << std::endl;
	std::cout << "S: " << static_cast<uint16_t>(this->S) << std::endl;
	std::cout << "P: " << static_cast<uint16_t>(this->P) << std::endl;
}

