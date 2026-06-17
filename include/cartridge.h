#include "common.h"
#include "mapper.h"
#include <iostream>
#include <vector>

struct Cartridge
{
	bool loadROM(const std::string& path); // Loads .nes file



private:
	std::vector<U8> m_prgROM; // Program ROM
	std::vector<U8> m_chrROM; // Character ROM

	// Mirror 
	std::unique_ptr<Mapper> m_mapper;
};