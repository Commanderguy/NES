#include "Core6502.h"
#define OPCODE(x) u8 Core6502:: ## x()
#define MODE(x) void Core6502:: ## x()


Core6502::Core6502(Bus<0xFFFF>* b, ptr ProgramCounter):
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