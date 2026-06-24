#include "mem.h"

void WRAM::Reset()
{
	for (int i = 0; i < 2048; i++)
	{
		this->m_wram[i] = 0;
	}
}

void WRAM::Write(U16 addr, U8 data)
{
	this->m_wram[addr] = data;
}

U8 WRAM::Read(U16 addr)
{
	return this->m_wram[addr];
}