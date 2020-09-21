#pragma once
#include "Types.h"

/// <summary>
/// Random access memory. To keep things structured, the Ram class is seperated instead of just a pointer to the heap.
/// </summary>
template<int idxs, int idxe, int actualSize>
class Ram
{
public:
	
	inline u8 Read(ptr loc);
	inline bool Write(ptr loc, u8 data);

	inline u8 ppuRead(ptr loc) { return _loc[loc & (actualSize - 1)]; };
	inline bool ppuWrite(ptr loc, u8 data) { return _loc[loc & (actualSize - 1)] = data; };

#ifndef _DEBUG
private:
#endif

	u8 _loc[actualSize];

protected:


};


template<int idxs, int idxe, int actualSize>
inline u8 Ram<idxs, idxe, actualSize>::Read(ptr loc)
{
	return _loc[loc & (actualSize - 1)];
}

template<int idxs, int idxe, int actualSize>
inline bool Ram<idxs, idxe, actualSize>::Write(ptr loc, u8 data)
{
	if (loc >= idxs && loc <= idxe) {
		_loc[loc & (actualSize - 1)] = data;
		return true;
	}
	return false;
}
