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
			m_frameComplete = true;
			//Status &= ~0x80;
		}
	}
}

U8 PPU::ReadRegister(U16 addr)
{
	switch (addr)
	{
	case 0x2002: // This could cause game stutters
	{
		U8 data = m_PPUSTATUS;

		// Read PPUSTATUS
		m_PPUSTATUS &= 0x7F; // clear VBlank flag
		m_toggleRW = false; // resets write toggle

		return data;
	}

	case 0x2004:
		return m_OAM[m_OAMAddr];

	case 0x2007:
	{
		// VRAM read logic later
		return 0;
	}

	default:
		return 0;

	}
}

void PPU::WriteRegister(U16 addr, U8 data)
{
	switch (addr)
	{
	case 0x2000:
		m_PPUCTRL = data;
		break;

	case 0x2001:
		m_PPUMASK = data;
		break;

	case 0x2003:
		m_OAMAddr = data;
		break;

	case 0x2004:
		m_OAM[m_OAMAddr++] = data; // TEST - Increase iteration before or after?
		// m_OAMAddr++;
		break;

	default:
		break;

	}
}

bool PPU::FrameComplete() const
{
	return m_frameComplete;
}

void PPU::ClearFrameFlag()
{
	m_frameComplete = false;
}

const std::array<uint32_t, 256 * 240>& PPU::GetFrameBuffer() const
{
	return m_frameBuffer;
}