#include "Mapper000.h"

// Reading program ROM
bool Mapper000::mapPRGRead(U16 addr, U16& mappedAddr)
{
	if (addr >= 0x8000) // Is CPU accessing cart?
	{
		mappedAddr = addr & (m_prgBanks > 1 ? 0x7FFF : 0x3FFF); // Bit mask for removing unwanted bits

		return true;
	}

	return false;
}

// 0x0000–0x07FF   RAM
// 0x2000–0x2007   PPU
// 0x8000–0xFFFF   prgROM

bool Mapper000::mapPRGWrite(U16 addr, U16& mappedAddr)
{
	return false;
}

bool Mapper000::mapCHRRead(U16 addr, U16& mappedAddr)
{
	return false;
}

bool Mapper000::mapCHRWrite(U16 addr, U16& mappedAddr)
{
	return false;
}