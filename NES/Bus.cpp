#include "Bus.h"
#include <memory>
#define TICK_READ(x, d) if(x##.willRead(d)) data = x##.Read(d);

u8 Bus::Read(ptr loc)
{
	u8 data = 0x00;
	TICK_READ(RAM, data)


	return data;
}

void Bus::Write(ptr loc, u8 data)
{
	
}

Bus::Bus()
{
	
}
