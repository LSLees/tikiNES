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