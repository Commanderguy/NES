#pragma once
#include <fstream>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

#include "Types.h"
#include "Bit.h"

/// <summary>
/// This struct is used to extract the hi bits out of a byte.
/// </summary>
struct HiByte
{
	u8 data;
	inline u8 get() { return data & 0xF0; }
};


/// <summary>
/// This struct represents the tv-system, but it basically just extracts bits 0 and 1, to generate a number.
/// This number can be either: 0: NTSC; 2: PAL; 1/3: dual compatible
/// </summary>
struct TvSystem
{
	u8 data;
	inline u8 get() { return data & 0x3; }
};


/// <summary>
/// The flags at byte 6 in the header.
/// </summary>
union Flags6
{
	u8 data;
	/// <summary>
	/// 0: horizontal (vertical arrangement) 
	/// 1: vertical	(horizontal arrangement)
	/// </summary>
	Bit<0> Mirroring;


	/// <summary>
	/// 1: The cartridge contains battery backed memory.
	/// </summary>
	Bit<1> ContainsPersistantMemory;


	/// <summary>
	/// 1: The file contains a 512 byte trainer.
	/// </summary>
	Bit<2> Trainer;


	/// <summary>
	/// 1: Ignore mirroring control.
	/// </summary>
	Bit<3> IgnoreMirror;


	/// <summary>
	/// The lower byte of the mapper number.
	/// </summary>
	HiByte getLoMapper;
};


/// <summary>
/// The flags at offset 7.
/// </summary>
union Flags7
{
	u8 data;
	/// <summary>
	/// VS Unisystem
	/// </summary>
	Bit<0> VsSystem;


	/// <summary>
	/// PlayChoice-10 (8KB of Hint Screen data stored after CHR data)
	/// </summary>
	Bit<1> PlayChoice;
	
	
	/// <summary>
	/// For Nes20Format3 
	/// </summary>
	Bit<2> Nes20Format2;


	/// <summary>
	/// If Nes20Format3 the .nes file is in nes20 format.
	/// </summary>
	Bit<3> Nes20Format3;


	/// <summary>
	/// Contains the hi byte of the mapper number.
	/// </summary>
	HiByte getHiMapper;
};


/// <summary>
/// These are not Flags, they are just documented as flags but really include the PRG-Ram size.
/// </summary>
typedef u8 Flags8;


/// <summary>
/// The byte with offset = 0x9 contains the informations for the tv system. Every bit aside the least significant have to be set to 0 and are reserved.
/// </summary>
union Flags9
{
	u8 data;
	/// <summary>
	/// The tv-system: 0: NTSC, 1: PAL
	/// </summary>
	Bit<0> TvSystem;
};



union Flags10
{
	u8 data;
	/// <summary>
	/// TV system (0: NTSC; 2: PAL; 1/3: dual compatible)
	/// </summary>
	TvSystem tv;


	/// <summary>
	/// 0: present; 1: not present
	/// </summary>
	Bit<4> PrgRam;


	/// <summary>
	/// 1: Board has bus conflicts
	/// </summary>
	Bit<5> BusConflict;
};



union header_s
{
	/// <summary>
	/// Placeholder data to ensure the size for the header and for easier interoperability with the filestream system.
	/// </summary>
	char _data[16] = "               ";
	struct _header
	{
		/// <summary>
		/// The nes header. The first 4 bytes should always be "NES<eof>"
		/// </summary>
		char nesHeader[4];


		/// <summary>
		/// The size of PRG-Rom in 16 kb units.
		/// </summary>
		u8 PRG_s;


		/// <summary>
		/// The size of the CHR-Rom in 8 kb units. (0: the rom uses CHR ram.
		/// </summary>
		u8 CHR_s;
		Flags6 f6;
		Flags7 f7;
		Flags8 f8;
		Flags9 f9;
		Flags10 f20;


		/// <summary>
		/// Padding at the and.
		/// </summary>
		u8 padding[5];

		std::string ToString();
	} header;
};




class iNesFile
{
public:
	header_s HEADER;

	u32 PRG_s;
	u8* PRG_ROM;

	u32 CHR_s;
	u8 CHR_ROM;

	u8* trainer; // Either 0 or 512 bytes, but we represent it as null or new u8[512].

	u8* InstRom; // Either 0 or 8192 bytes if present.

	u8* PROM; 


	iNesFile(const char* filename);
private:


protected:
	

};

