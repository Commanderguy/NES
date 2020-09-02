#include "Bus.h"

u8 Bus::Read(ptr loc)
{
	return PLACEHOLDERRAM[loc];
}

void Bus::Write(ptr loc, u8 data)
{
	PLACEHOLDERRAM[loc] = data;
}
