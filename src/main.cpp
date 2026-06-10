#include <iostream>
#include <fstream>
#include "../include/common.h"
#include "../include/cpu.h"
#include "../include/mem.h"


int main(int argc, char* argv[])
{
	CPU* cpu = new CPU;
	WRAM* wram = new WRAM;
	cpu->displayReg();

	// Open .nes file
	std::ifstream file("../test/Super Mario Bros. (World).nes", std::ios::binary);

	if (!file)
	{
		std::cout << "Failed\n";
		return 1;
	} 

	// Reading first 8 bytes
	unsigned char bytes[8];
	file.read(reinterpret_cast<char*>(bytes), 8);

	// Print first 8 bytes
	for (int i = 0; i < 8; i++)
	{
		std::cout << std::hex << (int)bytes[i] << ' ';
	}

	return 0;
}