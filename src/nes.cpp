#include "nes.h"

void NES::Reset()
{
	this->cpu.Reset(this);
	this->wram.Reset();
}