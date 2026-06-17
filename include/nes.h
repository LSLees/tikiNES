#pragma once
#include "../include/cpu.h"
#include "../include/mem.h"

struct NES
{
	CPU cpu;
	WRAM wram;

	NES();
};