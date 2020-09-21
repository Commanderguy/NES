#pragma once
#include "Types.h"

class Mapper
{
public:
	virtual inline bool Read(ptr loc, u8&) = 0;
	virtual inline bool Write(ptr loc, u8 data) = 0;

	virtual inline bool ppuRead(ptr loc, u8&) = 0;
	virtual inline bool ppuWrite(ptr loc, u8 data) = 0;

	Mapper(u8* PRG_ptr, u8* CHR_ptr) : PRG_ROM{ PRG_ptr }, CHR_ROM{ PRG_ptr } {};
private:

protected:

	u8* PRG_ROM;
	u8* CHR_ROM;

};

