#pragma once

#include <array>

struct PPU
{
	void Step();

	// Reset PPU state
	void Reset();

	// One cycle
	void Clock();

	U8 Status = 0;

private:

	// Connect cartridge
	Cartridge* m_cartridge = nullptr;

	// Internal VRAM (2KB)
	std::array<U8, 2048> m_nameTables{};




	// Timing
	int m_cycle = 0;
	int m_scanline = 0;

	bool m_frameCompleted = false;



};