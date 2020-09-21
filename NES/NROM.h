#pragma once
#include "Mapper.h"

class NROM : public Mapper
{
public:
	// Methods inherited from Mapper
	virtual bool Read(ptr loc, u8&) override;
	virtual bool Write(ptr loc, u8 data) override;
	virtual bool ppuRead(ptr loc, u8&) override;
	virtual bool ppuWrite(ptr loc, u8 data) override;

	// Constructor and destructor
	NROM(u8* PRG_ptr, u8* CHR_ptr, bool kb) : Mapper(PRG_ptr, CHR_ptr), kb256{ kb } {};
	~NROM() {};


private:

	bool kb256;
};

