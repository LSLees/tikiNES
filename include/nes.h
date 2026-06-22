#pragma once
#include "cpu.h"
#include "mem.h"
#include "cartridge.h"

struct Mapper;

struct NES
{
	CPU cpu;
	WRAM wram;
	Cartridge cart;
	Mapper* mapper;

	void Reset();
	bool InitMapper(U8 mID);
};