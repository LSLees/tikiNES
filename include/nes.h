#pragma once
#include "cpu.h"
#include "ppu.h"
#include "mem.h"
#include "cartridge.h"

struct Mapper;

struct NES
{
	bool running = true;

	CPU cpu;
	PPU ppu;
	WRAM wram;
	Cartridge cart;
	Mapper* mapper;

	void Reset(char* rom);
	bool InitMapper(U8 mID);

	U8 Read(U16 addr);
	void Write(U16 addr, U8 data);
	void Step();
};