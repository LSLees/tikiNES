#pragma once
#include <array>
#include "common.h"

struct NES;

struct PPU
{
	void Step();
	void Reset();

	// Reset PPU state
	void Reset(NES* nes);

	// One cycle
	void Clock();

	U8 Status = 0;

private:

	// Connect cartridge
	NES* m_NES = nullptr;

	// Internal VRAM (2KB)
	std::array<U8, 2048> m_nameTables{};




	// Timing
	int m_cycle = 0;
	int m_scanline = 0;

	bool m_frameCompleted = false;



};