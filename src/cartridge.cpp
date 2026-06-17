#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstring>

#include "cartridge.h"


bool Cartridge::loadROM(char* path)
{
	path = "Super Mario Bros. (World).nes";

	std::vector<U8> file;
	std::ifstream f(path, std::ios::binary);

	return false;
}