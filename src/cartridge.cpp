#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstring>

#include "cartridge.h"


bool Cartridge::loadROM(Cartridge* cart, char* path)
{
	path = "Super Mario Bros. (World).nes";

	// Open .nes file
	std::ifstream rom(path, std::ios::binary);

	if (!rom.is_open())
	{
		std::cout << "Failed to open rom" << std::endl;
		return false;
	}
	
	std::cout << "Printing header:" << std::endl;

	U8 header[16];
	rom.read(reinterpret_cast<char*>(header), sizeof(header));
	
	for (int i = 0; i < sizeof(header); i++)
	{
		std::cout << std::dec << i << ": ";
		std::cout << std::hex << static_cast<int>(header[i]) << std::endl;
	}

	// Check valid iNes header
	if (header[0] != 0x4e || header[1] != 0x45 || header[2] != 0x53 || header[3] != 0x1a)
	{
		std::cout << "Not valid NES ROM" << std::endl;
		return false;
	}

	U8 mapperID = (header[6] >> 4) | header[7] & 0xF0;
	std::cout << std::endl << "mapperID: " << static_cast<int>(mapperID) << std::endl;

	int prgROMStart = (header[6] && 0xb100) != 0 ? 528 : 16;
	cart->m_prgROM.resize(header[4] * 16000);

	return true;
}