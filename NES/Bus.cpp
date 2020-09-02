#include "Bus.h"
#include <memory>

u8 Bus::Read(ptr loc)
{
	return PLACEHOLDERRAM[loc];
}

void Bus::Write(ptr loc, u8 data)
{
	PLACEHOLDERRAM[loc] = data;
}

Bus::Bus()
{
	memset(PLACEHOLDERRAM, 0, 0xFFFF);
}
