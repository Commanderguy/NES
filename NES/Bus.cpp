#include "Bus.h"
#include <memory>

u8 Bus::Read(ptr loc)
{
	u8 data = 0x00;


	return data;
}

void Bus::Write(ptr loc, u8 data)
{
	PLACEHOLDERRAM[loc] = data;
}

Bus::Bus()
{
	memset(PLACEHOLDERRAM, 0, 0xFFFF);
}
