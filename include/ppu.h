#pragma once
#include <array>
#include "common.h"

struct NES;

struct PPU
{
	// Reset PPU state
	void Reset(NES* nes);

	// Three cycles
	void Step();

	// CPU access to the PPU registers
	U8 ReadRegister(U16 addr);
	void WriteRegister(U16 addr, U8 data);


	bool FrameComplete() const; // Checks frame state
	void ClearFrameFlag();


	const std::array<uint32_t, 256 * 240>& GetFrameBuffer() const;

	U8 Status = 0;

private:

	// Connect cartridge
	NES* m_NES = nullptr;

	// Internal VRAM (2KB)
	std::array<U8, 2048> m_nameTables{};




	// Timing
	int m_cycle = 0;
	int m_scanline = 0;

	bool m_frameComplete = false;



};