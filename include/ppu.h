#pragma once
#include <array>
#include "common.h"

struct NES;

struct PPU
{
	// Reset PPU state and connects NES to PPU
	void Reset(NES* nes);

	// Three cycles
	void Step();

	// CPU access to the PPU registers
	U8 ReadRegister(U16 addr);
	void WriteRegister(U16 addr, U8 data);


	bool FrameComplete() const; // Checks frame state

	//void ClearFrameFlag(); // Not needed here?


	const std::array<uint32_t, 256 * 240>& GetFrameBuffer() const;

	U8 Status = 0;

private:

	// Connect cartridge
	NES* m_NES = nullptr;

	// PPU Registers
	U8 m_PPUCTRL = 0; // $2000 - Writeable
	U8 m_PPUMASK = 0; // $2001 - Writeable
	U8 m_PPUSTATUS = 0; // $2002 - Readable

	U8 m_OAMAddr = 0; // $2003 - Writeable

	// Internal Registers (on nesDev.org)
	U16 m_v = 0; // Current VRAM Address
	U16 m_t = 0; // Temp VRAM Address

	U8 m_fineX = 0; // Position of current scroll
	bool m_toggleRW = false; // 

	// Sprite Memory
	std::array<U8, 256> m_OAM{};

	// Timing
	int m_cycle = 0;
	int m_scanline = 0;

	bool m_frameComplete = false;

	// Output Frame Buffer, for SDL
	std::array<uint32_t, 256 * 240> m_frameBuffer{};


};