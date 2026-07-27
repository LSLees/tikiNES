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

	void Step(); // 
	
	//CPU Bus
	U8 Read(U16 addr); // CPU Read
	void Write(U16 addr, U8 data); // CPU Write

	// PPU Bus
	U8 PPURead(U16 addr); // PPU Read
	void PPUWrite(U16 addr, U8 data); // PPU Write

private:
	
};