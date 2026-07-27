#include "ppu.h"
void PPU::Step()
{
	cycle++;

	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;

		if (scanline == 241)
		{
			status |= 0x80;
		}

		if (scanline >= 262)
		{
			scanline = 0;
			status &= ~0x80;
		}
	}
}