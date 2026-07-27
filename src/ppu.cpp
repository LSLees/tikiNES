#include "ppu.h"

void PPU::Reset(NES* nes)
{
	m_NES = nes;
}

void PPU::Step()
{
	m_cycle++;

	if (m_cycle >= 341)
	{
		m_cycle = 0;
		m_scanline++;

		if (m_scanline == 241)
		{
			Status |= 0x80;
		}

		if (m_scanline >= 262)
		{
			m_scanline = 0;
			Status &= ~0x80;
		}
	}
}

