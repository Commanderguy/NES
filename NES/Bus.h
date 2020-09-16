#pragma once
#include "Types.h"
#include "Ram.h"
#include "Device.h"



class Bus
{
public:
	u8 Read(ptr loc);
	void Write(ptr loc, u8 data);
	Bus();

	///////////////// Devices ///////////////////
	Ram<0x0000, 0x1FFF, 2048> RAM;


private:

protected:

};

