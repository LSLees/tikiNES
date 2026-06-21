#include "common.h"
#include <iostream>
#include <vector>

struct NES;

struct Cartridge
{
	bool loadROM(Cartridge* cart, char* path);

private:
	std::vector<U8> m_prgROM; // Program ROM
	std::vector<U8> m_chrROM; // Character ROM
};