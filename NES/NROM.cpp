#include "NROM.h"

bool NROM::Read(ptr loc, u8& sav)
{
    if (loc >= 0x8000 && loc <= 0xFFFF)
    {
        sav = PRG_ROM[loc & (kb256 ? 0x7FFF : 0x3FFF)];

        return true;
    }
    return false;
}

bool NROM::Write(ptr loc, u8 data)
{
    if (loc >= 0x8000 && loc <= 0xFFFF)
    {
        PRG_ROM[loc & (kb256 ? 0x7FFF : 0x3FFF)] = data;

        return true;
    }
    return false;
}

bool NROM::ppuRead(ptr loc, u8& sav)
{
    if (loc >= 0x0000 && loc <= 0x1FFF)
    {
        sav = CHR_ROM[loc];
        return true;
    }
    return false;
}

bool NROM::ppuWrite(ptr loc, u8 data)
{
    return false;
}
