#pragma once
#include "cpu.h"
#include "mem.h"
#include "cartridge.h"

struct NES
{
	CPU cpu;
	WRAM wram;
	Cartridge cart;

	void Start();
};