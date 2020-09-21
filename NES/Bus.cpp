#include "Bus.h"
#include <memory>
#define TICK_READ(x, d) if(x##.willRead(d)) data = x##.Read(d);
#define TICK_WRITE(x, l, c) if(x##.willRead(l)) x##.Write(l, c);

u8 Bus::Read(ptr loc)
{
	u8 data = 0x00;
	
	return data;
}

void Bus::Write(ptr loc, u8 data)
{
	
}

Bus::Bus()
{
	
}
