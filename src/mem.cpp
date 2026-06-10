#include "../include/mem.h"

void WRAM::wramWrite(U16 addr, U16 data)
{
	this->m_wram[addr] = data;
}

U16 WRAM::wramRead(U16 addr)
{
	return this->m_wram[addr];
}