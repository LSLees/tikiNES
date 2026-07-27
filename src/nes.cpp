#include <iostream>
#include <thread>
#include <chrono>

#include "nes.h"
#include "mapper000.h"

void NES::Reset(char* rom)
{
	cart.loadROM(rom);
	InitMapper(cart.mID);

	cpu.Reset(this);
	ppu.Reset(this);
	wram.Reset();

	std::cout << "Reset vector- " << static_cast<U16>(cpu.PC) << std::endl;
	std::cout << "Running- " << rom << std::endl;

	Step();
}

void NES::Step()
{
	bool running = true;
	while (running)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		U8 cyc = cpu.Step();
		for (int i = 0; i < cyc * 3; i++)
		{
			ppu.Step();
		}
	}
}

bool NES::InitMapper(U8 mID)
{
	switch (mID)
	{
	case 0:
	{
		std::cout << "Using mapper- NROM" << std::endl;
		this->mapper = new Mapper000;
		return true;
	}
	default:
	{
		std::cout << "No valid mapper for ROM!" << std::endl;
		return false;
	}
	}
}

U8 NES::Read(U16 addr)
{
	U16 mapped;

	if (addr <= 0x1fff) // WRAM
	{
		return wram.Read(addr & 0x07ff);
	}
	else if (addr <= 0x3fff) // PPU
	{
		return 0;
	}
	else if (addr <= 0x4017) // APU/IO
	{
		return 0;
	}
	else if (addr >= 0x8000)
	{
		if (mapper->mapPRGRead(addr, mapped))
		{
			return cart.prgRead(mapped);
		}
	}

	return 0;
}

void NES::Write(U16 addr, U8 data)
{
	U16 mappedAddr;

	if (addr <= 0x1fff) // WRAM
	{
		wram.Write(addr & 0x07ff, data);
	}
	else if (addr <= 0x3fff) // PPU
	{
		return;
	}
	else if (addr <= 0x4017) // APU/IO
	{
		return;
	}
	else if (addr >= 0x8000)
	{
		if (mapper->mapPRGWrite(addr, mappedAddr))
		{
			cart.prgWrite(mappedAddr, data);
		}
	}
}

U8 NES::PPURead(U16 addr)
{
	return addr;
}

void NES::PPUWrite(U16 addr, U8 data)
{
	return;
}