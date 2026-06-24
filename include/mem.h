#pragma once
#include "common.h"

struct WRAM
{
private:
		U8 m_wram[2048];

public:
	void Reset();
	void Write(U16 addr, U8 data);
	U8 Read(U16 addr);
};

/*
0x0000–0x07ff   2KB RAM
0x0800–0x1fff   Mirror of above
0x2000–0x2007   PPU registers
0x2008–0x3fff   Mirror of PPU registers
0x4000–0x4017   APU and IO registers
0x4018–0x7fff   Cartridge space
0x8000–0xffff   Cartridge; PRG, ROM
*/