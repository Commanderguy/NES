#pragma once
#include "Types.h"
#include "Device.h"


/// <summary>
/// Random access memory. To keep things structured, the Ram class is seperated instead of just a pointer to the heap.
/// </summary>
template<int idxs, int idxe, int actualSize>
class Ram : public Device<idxs, idxe>
{
public:
	
	inline u8 Read(ptr loc) override;
	inline void Write(ptr loc, u8 data) override;

private:
	u8 _loc[actualSize];

protected:


};

