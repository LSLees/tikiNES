#pragma once
#include "common.h"


enum MapperType
{
    NROM = 0
    /*SxROM = 1,
    UxROM = 2,
    CNROM = 3,
    MMC3 = 4,
    AxROM = 7,
    ColorDreams = 11,
    GxROM = 66,*/
};

struct Mapper
{
    virtual bool mapPRGWrite(U16 addr, U16& mappedAddr) = 0;
    virtual bool mapPRGRead(U16 addr, U16& mappedAddr) = 0;

    virtual bool mapCHRWrite(U16 addr, U16& mappedAddr) = 0;
    virtual bool mapCHRRead(U16 addr, U16& mappedAddr) = 0;
};