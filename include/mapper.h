#include "common.h"

struct Mapper
{
    enum Type
    {
        NROM = 0, // 
        /*SxROM = 1,
        UxROM = 2,
        CNROM = 3,
        MMC3 = 4,
        AxROM = 7,
        ColorDreams = 11,
        GxROM = 66,*/
    };

    virtual void writePRG();
    virtual U8 readPRG();

    virtual void writeCHR();
    virtual U8 readCHR();
};