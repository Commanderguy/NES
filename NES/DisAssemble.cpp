#include "DisAssemble.h"

DisAssemble::DisAssemble(u8 byte, u8 next[3])
{
    symbol = symbols[byte];
    size = lenghttable[byte];
}

std::string hex(uint32_t n, uint8_t d)
{
    std::string s(d, '0');
    for (int i = d - 1; i >= 0; i--, n >>= 4)
        s[i] = "0123456789ABCDEF"[n & 0xF];
    return s;
};

std::string DisAssemble::_toString() const
{
    std::string s = symbol;
    s += " ";
    // Wrap the arguments in the correct form.
   ToPtr t;
    switch (am)
    {
    case imm: 
        s += "#";
        s += std::to_string(_nBytes[0]);
        break;
    case imp:
        break;
    case acc:
        s += "A";
        break;
    case zp:
        s += "$";
        s += hex(_nBytes[0], 2);
        break;
    case zpx:
        s += "$";
        s += hex(_nBytes[0], 2);
        s += ",X";
        break;
    case zpy:
        s += "$";
        s += hex(_nBytes[0], 2);
        s += ",Y";
        break;
    case rel:
        s += std::to_string((int)((signed char)_nBytes[0]));
        break;
    case oabs:
        s += "$";
        t.lo = _nBytes[0];
        t.hi = _nBytes[0];
        s += hex(t.p, 4);
        break;
    case abx:
        s += "$";
        t.lo = _nBytes[0];
        t.hi = _nBytes[0];
        s += hex(t.p, 4);
        s += ",X";
        break;
    case aby:
        s += "$";
        t.lo = _nBytes[0];
        t.hi = _nBytes[1];
        s += hex(t.p, 4);
        s += ",Y";
        break;
    case ind:
        s += "($";
        t.lo = _nBytes[0];
        t.hi = _nBytes[1];
        s += hex(t.p, 4);
        s += ")";
        break;
    case izx:
        s += ("($");
        s += hex(_nBytes[0], 2);
        s += (",X)");
        break;
    case izy:
        s += ("($");
        s += hex(_nBytes[0], 2);
        s += ("),Y");
    default:
        std::cout << "addressing mode " << am << "is not mapped yet" << std::endl;
    }
    // Assemble a comment containing all extra information.
    return s;
}
