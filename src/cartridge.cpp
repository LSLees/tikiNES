#include <fstream>
#include <iostream>

#include "cartridge.h"


bool Cartridge::loadROM(char* path)
{
	std::cout << "Reading- " << path << "- ";

	// Open .nes file
	std::ifstream rom(path, std::ios::binary);

	if (!rom.is_open())
	{
		std::cout << "Failed!" << std::endl;
		return false;
	}

	std::cout << "Success!" << std::endl;

	// Get header bytes 0-15
	U8 header[16];
	rom.read(reinterpret_cast<char*>(header), sizeof(header));
	std::cout << "Header- ";

	// Check valid iNes header
	if (header[0] != 0x4e || header[1] != 0x45 || header[2] != 0x53 || header[3] != 0x1a)
	{
		std::cout << "Not valid NES ROM" << std::endl;
		return false;
	}

	// Print header
	for (int i = 0; i < sizeof(header); i++)
	{
		std::cout << std::hex << static_cast<int>(header[i]) << " ";
	}

	std::cout << std::endl;

	// Set mapper
	this->mID = (header[6] >> 4) | (header[7] & 0xF0);


	// Parse prgROM
	std::cout << "Parsing prgROM- ";

	if (header[6] & 0x04)
	{
		rom.seekg(512, std::ios::cur);
	}

	int prgSize = header[4] * 16384;
	this->m_prgROM.resize(prgSize);
	
	if (!rom.read(reinterpret_cast<char*>(this->m_prgROM.data()), prgSize))
	{
		std::cout << "Failed!" << std::endl;
		return false;
	}

	std::cout << "Success!" << std::endl;

	// Parse chrROM
	std::cout << "Parsing chrROM- ";

	int chrSize = header[5] * 8192;
	this->m_chrROM.resize(chrSize);

	if (!rom.read(reinterpret_cast<char*>(this->m_chrROM.data()), chrSize))
	{
		std::cout << "Failed!" << std::endl;
		return false;
	}

	std::cout << "Success!" << std::endl;

	return true;
}

U8 Cartridge::prgRead(U16 addr)
{
	return m_prgROM[addr];
}

void Cartridge::prgWrite(U16 addr, U8 data)
{
	m_prgROM[addr] = data;
}