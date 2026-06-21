#include "nes.h"

void NES::Reset()
{
	this->cpu.Reset(this);
	this->wram.Reset();
}

void NES::InitMapper(MapperType type)
{
	//Mapper* mapper = new
}