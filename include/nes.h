#pragma once
#include "cpu.h"
#include "mem.h"
#include "cartridge.h"

enum MapperType;

struct NES
{
	CPU cpu;
	WRAM wram;
	Cartridge cart;

	void Reset();
	void InitMapper(MapperType type);
};