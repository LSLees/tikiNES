#include "../include//nes.h"

NES::NES()
{
	this->cpu.Reset(this);
	this->wram.Reset();
}