#include <fstream>
#include "cartridge.h"


bool Cartridge::loadROM(const std::string& path)
{
	std::ifstream file("../test/Super Mario Bros. (World).nes", std::ios::binary);

	if (!file)
	{
		return false;
	}

	// Diesect iNes header for mapper values
}
