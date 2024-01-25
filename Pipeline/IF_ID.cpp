//
//  IF_ID.cpp


#include "IF_ID.hpp"
#include <iostream>
#include <iomanip>

IF_ID::IF_ID() {}

int64_t IF_ID::get_instruction()
{
    return instruction;
}

int64_t IF_ID::set_instruction(int64_t ins)
{
    instruction = ins;
    return instruction;
}

void IF_ID::print() const {
    cout << "Inst = 0x" << setfill('0') << setw(8)
    << hex << instruction << endl;

}
