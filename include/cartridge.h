#include "common.h"
#include "mapper.h"
#include <iostream>
#include <vector>

struct Header // First 16 bytes of ROM
{
	U8 prgSize; // Size of PRG ROM * 16KB
	U8 chrSize; // Size of CHR ROM * 8 KB
	U8 flags6;
	U8 flags7;
	U8 mapperID;
	U8 trainer;
};

struct Cartridge
{
	bool loadROM(char* path); // Loads ROM

private:
	Header header;
	std::vector<U8> m_prgROM; // Program ROM
	std::vector<U8> m_chrROM; // Character ROM

	// Mirror
	std::unique_ptr<Mapper> m_mapper;
};