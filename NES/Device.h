#pragma once
#include "Types.h"

template <int startIdx, int endIdx>
class Device
{
public:
	inline const bool willRead(const ptr address);
	virtual inline u8 Read(ptr loc) = 0;
	virtual inline void Write(ptr loc, u8 data) = 0;
};
