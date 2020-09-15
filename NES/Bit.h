#pragma once
#include "Types.h"
/// <summary>
/// The bit class is used to set, clear get, and toggle a bit in a union.
/// </summary>
template <int bitPlace, typename unionType = u8>
class Bit
{
	unionType data;
public:
	bool Get() { return (data >> bitPlace) & 1; }
	void Set() { data |= 1 << bitPlace; }
	void Clear() { data &= ~(1 << bitPlace); }
	void Toggle() { data ^= 1 << bitPlace; }
	inline void operator= (bool b);
};

template<int bitPlace, typename unionType>
inline void Bit<bitPlace, unionType>::operator=(bool b)
{
	if (b)
		Set();
	else
		Clear();
}
