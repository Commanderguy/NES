#include "Core6502.h"
#define OPCODE(x) u8 Core6502:: ## x()
#define MODE(x) void Core6502:: ## x()

Core6502::Core6502(Bus* b, ptr ProgramCounter):
	_bus {b},
	ProgramCounter {ProgramCounter}
{
}

OPCODE(XXX)
{
	throw "This opcode has not been implemented yet";
}


/// <summary>
/// No operation. We just return the cycle count which is 2.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
OPCODE(NOP)
{
	return 2;
}


/// <summary>
/// Implied/Implicit. The operand is defined by the instruction, and we don't need to operate on a address on the ram.
/// </summary>
MODE(IMP)
{

}


/// <summary>
/// Zeropage adressing mode. The adresses high byte is always 0x00 and the low byte is provided by the next byte.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(_ZP)
{
	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// Absolute addressing mode. Similar to zero page adressing mode, but this time, the high byte is also included in the program.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ABS)
{
	ToPtr t;
	t.p = 0;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// AccumulatorAdressingMode. The Accumulator addressing mode is a special version of the immediate mode for working on the acummulator.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(AAM)
{

}


/// <summary>
/// Immediate mode: There is nothing to do here. It's the same as implied, but opcodes that work with implied have arguments specified in the next byte
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(IMM)
{

}


/// <summary>
/// Relative mode. The relative mode operates on the program counter + the value in the next byte. The next byte has to be read as a signed number, so the range is -127 - 127
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(REL)
{
	ToPtr t;
	t.lo = 0;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = ProgramCounter + ((signed char)(t.p));
}


/// <summary>
/// Indirect addressing is only used by a special type of JMP. The operate address is set to the pointer found at the address specified in the memory that get's pointed to by the next two bytes.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(IND)
{
	ToPtr t;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	
	ToPtr f;
	f.lo = _bus->Read(t.p);
	t.p++;
	f.hi = _bus->Read(t.p);
	addressOperate = f.p;
}


/// <summary>
/// Zero page address mode with x index. The address to operate on is the content of the next byte + x.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ZPX)
{
	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter) + x;
	ProgramCounter++;
	addressOperate = t.p;
}

/// <summary>
/// Zero page address mode with x index. The address to operate on is the content of the next byte + y.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ZPY)
{

	ToPtr t;
	t.hi = 0x00;
	t.lo = _bus->Read(ProgramCounter) + y;
	ProgramCounter++;
	addressOperate = t.p;
}


/// <summary>
/// Absolute addressing mode indexed with the x register.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ABX)
{
	ToPtr t;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p + x;
}


/// <summary>
/// Absolute addressing mode indexed with t´he y register
/// </summary>
/// <param name=""></param>
/// <returns></returns>
MODE(ABY)
{
	ToPtr t;
	t.lo = _bus->Read(ProgramCounter); // First lo, then hi byte. The 6502 is a little endian machine.
	ProgramCounter++;
	t.hi = _bus->Read(ProgramCounter);
	ProgramCounter++;
	addressOperate = t.p + y;
}