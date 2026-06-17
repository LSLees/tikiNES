#pragma once
#include "common.h"

struct WRAM
{
private:
		U16 m_wram[64000];

public:
	void Reset();
	void Write(U16 addr, U16 data);
	U8 Read(U16 addr);
};