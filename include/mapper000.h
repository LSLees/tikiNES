#include "common.h"

#include "mapper.h"

struct Mapper000 : public Mapper
{
	Mapper000(U8 prgBanks, U8 chrBanks);

	bool mapPRGRead(U16 addr, U16& mappedAddr) override;
	bool mapPRGWrite(U16 addr, U16& mappedAddr) override;

	bool mapCHRRead(U16 addr, U16& mappedAddr) override;
	bool mapCHRWrite(U16 addr, U16& mappedAddr) override;

private:
	U8 m_prgBanks;
	U8 m_chrBanks;
};