#pragma once
#include "../include/common.h"

struct WRAM
{
private:
		U16 m_wram[64000];

public:
	void wramWrite(U16 addr, U16 data);
	U16 wramRead(U16 addr);
};