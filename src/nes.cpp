#include <iostream>

#include "nes.h"
#include "mapper000.h"

void NES::Reset()
{
	this->cpu.Reset(this);
	this->wram.Reset();
}

bool NES::InitMapper(U8 mID)
{
	switch (mID)
	{
	case 0:
	{
		std::cout << "Using mapper- NROM" << std::endl;
		this->mapper = new Mapper000;
		return true;
	}
	default:
	{
		std::cout << "No valid mapper for ROM!" << std::endl;
		return false;
	}
	}
}