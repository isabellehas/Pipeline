//
//  EX_Mem.cpp


#include "EX_Mem.hpp"

EX_Mem::EX_Mem() {}

// Instructions get and set
int EX_Mem::get_ALU_result()
{
    return ALU_result;
}
void EX_Mem::set_ALU_result(int ALU)
{
    ALU_result = ALU;
}

int EX_Mem::get_sw_value()
{
    return sw_value;
}
void EX_Mem::set_sw_value(int swval)
{
    sw_value = swval;
}

string EX_Mem::get_write_regnum()
{
    return write_regnum;
}
void EX_Mem::set_write_regnum(int num)
{
    if (mem2reg_ex == "X" )// sw
    {
        write_regnum = "X";
    }
    else
    {
        write_regnum = to_string(num);
    }
}

// Control bits get and set
bool EX_Mem::get_mem_read_ex()
{
    return  mem_read_ex;
}
void EX_Mem::set_mem_read_ex(bool memread)
{
    mem_read_ex = memread;
}

bool EX_Mem::get_mem_write_ex()
{
    return mem_write_ex;
}
void EX_Mem::set_mem_write_ex(bool memwrite)
{
    mem_write_ex = memwrite;
}

bool EX_Mem::get_reg_write_ex()
{
    return  reg_write_ex;
}
void EX_Mem::set_reg_write_ex(bool regw)
{
    reg_write_ex = regw;
}

std::string EX_Mem::get_mem2reg_ex()
{
    return mem2reg_ex;
}
void EX_Mem::set_mem2reg_ex(string mem2reg_)
{
    mem2reg_ex = mem2reg_;
}


void EX_Mem::print(){
    cout << "Control: MemRead = " << mem_read_ex << ", " << "MemWrite = " << mem_write_ex << ", "
    << "Branch = 0" << endl;
    cout << "MemToReg = " << mem2reg_ex << ", " << "RegWrite = " << reg_write_ex << endl;
    cout << "CalcBTA = X, Zero = F, ALUResult = " << hex << ALU_result << endl;
    cout << "SWValue = " << sw_value << ", " << "WriteRegNum = " << write_regnum << endl;
}
