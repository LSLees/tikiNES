#include <vector>

#include "common.h"

struct NES;

struct Cartridge
{
	U8 mID; // Maybe just return this value with loadROM()

	bool loadROM(char* path);

private:
	std::vector<U8> m_prgROM; // Program ROM
	std::vector<U8> m_chrROM; // Character ROM
};