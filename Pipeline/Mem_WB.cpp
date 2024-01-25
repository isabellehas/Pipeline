//
//  Mem_WB.cpp
//

#include "Mem_WB.hpp"
Mem_WB::Mem_WB() {}

string Mem_WB::get_lw_val()
{
    return lw_val;
}
void Mem_WB::set_lw_val(int lwval)
{
    if(lwval == 0)
    {
        lw_val = "X";
    }
    else
    {
        stringstream lw_hex;
        lw_hex << hex << lwval;
        string temp(lw_hex.str());
        lw_val = temp;
    }

}

int Mem_WB::get_ALU_result_mm()
{
    return ALU_result_mm;
}
int Mem_WB::set_ALU_result_mm(int alu)
{
    ALU_result_mm = alu;
    return ALU_result_mm;
}

string Mem_WB::get_write_regnum_mm()
{
    return write_regnum_mm;
}
string Mem_WB::set_write_regnum_mm(string w_reg)
{
    write_regnum_mm = w_reg;
    return write_regnum_mm;
}

string Mem_WB::get_mem2reg_mm()
{
    return mem2reg_mm;
}
string Mem_WB::set_mem2reg_mm(string mem2reg_mm_)
{
    mem2reg_mm = mem2reg_mm_;
    return mem2reg_mm;
}

bool Mem_WB::get_reg_write_mm()
{
    return reg_write_mm;
}
bool Mem_WB::set_reg_write_mm(bool reg_write_mm_)
{
    reg_write_mm = reg_write_mm_;
    return reg_write_mm;
}


void Mem_WB::print(){
    cout << "Control: MemToReg = " << mem2reg_mm << ", "
    << "RegWrite = " << reg_write_mm << endl;
    cout << "LWDataValue = " << lw_val << ", " << "ALUResult = " << ALU_result_mm << ", "
    << "WriteRegNum = " << write_regnum_mm << endl;
}
