#include "nes.h"

void NES::Start()
{
	this->cpu.Reset(this);
	this->wram.Reset();
}