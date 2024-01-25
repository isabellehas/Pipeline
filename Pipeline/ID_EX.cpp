//
//  ID_EX.cpp
//

#include "ID_EX.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

/*

set_opcode(ins) == 0 | R type | reg_dst=1 | ALU_op=10 | ALU_src=0 | Reg_write=1
set_opcode(ins) == 0x20 | lw | reg_dst=0 | ALU_op=00 | ALU_src=1 | Reg_write=1
set_opcode(ins) == 0x28 | sw | reg_dst=X | ALU_op=00 | ALU_src=X | Reg_write=0

*/

ID_EX::ID_EX() {}

int64_t ID_EX::getinstruction_ex()
{
    return instruction;
}

int64_t ID_EX::setinstruction_ex(int64_t ins)
{
    instruction = ins;
    return instruction;
}


int ID_EX::get_readreg_1()
{
    return readreg1;
}
int ID_EX::set_readreg_1(int64_t ins, int Register[])
{
    int src_reg1 = (ins & 0x03E00000) >> 21;
    readreg1 = Register[src_reg1];
    
    return readreg1;
}
/*
int ID_EX::set_readreg_1(int64_t ins, int Register[])
{
    if(ins == 0){
        readreg1 = 0;
    }
    else{
        int src_reg1 = (ins & 0x03E00000) >> 21;
        readreg1 = Register[src_reg1];
    }
    return readreg1;
}
*/
int ID_EX::get_readreg_2()
{
    return readreg2;
}
int ID_EX::set_readreg_2(int64_t ins, int* Regs)
{
    if(ins == 0){
        readreg1 = 0;
    }
    else{
        int src_reg2 = (ins & 0x001F0000) >> 16;
        readreg2 = Regs[src_reg2];
    }
    return readreg2;
}

short ID_EX::get_offset()
{
    return offset;
}
string ID_EX::get_offset_code()
{
    return offset_code;
}
void ID_EX::set_offset(int64_t ins)
{
    offset = (ins & 0x0000FFFF) << 16;
    offset = offset >> 16;
    
}
string ID_EX::set_offset_code(int64_t ins)
{
    if (set_opcode(ins) == 0x20 || set_opcode(ins) == 0x28)
    {
        set_offset(ins);
        int off = get_offset();
        stringstream off_hex;
        off_hex << hex << off;
        //string off_str = std::to_string(off_hex);
        string off_str(off_hex.str());
        offset_code = off_str;
        return offset_code;
    }
    else
    {
        offset_code = "X";
        return offset_code;
    }
    return 0;
}

int ID_EX::get_writereg_20_16()
{
    return writereg_20_16;
}
int ID_EX::set_writereg_20_16(int64_t ins)
{
    writereg_20_16 = (ins & 0x001F0000) >> 16;
    return writereg_20_16;
}

int ID_EX::get_writereg_15_11()
{
    return writereg_15_11;
}
int ID_EX::set_writereg_15_11(int64_t ins)
{
    writereg_15_11 = (ins & 0x0000F800) >> 11;
    return writereg_15_11;
}

int ID_EX::get_opcode()
{
    return opcode;
}
int ID_EX::set_opcode(int64_t ins)
{
    opcode = (ins & 0xFC000000) >> 26;
    return opcode;
}

int ID_EX::get_function()
{
    return function;
}
std::string ID_EX::get_function_code()
{
    return func_code;
}

int ID_EX::set_function(int64_t ins)
{
    function = (ins & 0x0000003F);
    return function;
}
string ID_EX::set_function_code(int64_t ins)
{
    if (set_opcode(ins) == 0)
    {
        int func = set_function(ins);
        std::stringstream func_hex;
        func_hex << hex << func;
        //func_code = std::to_string(func_hex);
        string temp2(func_hex.str());
        func_code = temp2;
        return func_code;
    }
    else
    {
        func_code = "X";
        return func_code;
    }
    return func_code;
}

string ID_EX::get_reg_dst()
{
    return reg_dst;
}
string ID_EX::set_reg_dst(int64_t ins)
{
    if (set_opcode(ins) == 0)
    {
        reg_dst = "1";
        return reg_dst;
    }
    else if (set_opcode(ins) == 0x20)
    {
        reg_dst = "0";
        return reg_dst;
    }
    else if (set_opcode(ins) == 0x28)
    {
        reg_dst = "X";
        return reg_dst;
    }
    return 0;
}


int ID_EX::get_ALU_op()
{
    return ALU_op;
}
int ID_EX::set_ALU_op(int64_t ins)
{
    if (set_opcode(ins) == 0)
    {
        ALU_op = 10;
        return ALU_op;
    }
    else
    {
        ALU_op = 00;
        return ALU_op;
    }
    return 0;
}

bool ID_EX::get_ALU_src()
{
    return ALU_src;
}
bool ID_EX::set_ALU_src(int64_t ins)
{
    if (set_opcode(ins) == 0)
    {
        ALU_src = 0;
        return ALU_src;
    }
    else
    {
        ALU_src = 1;
        return ALU_src;
    }
    return 0;
}

bool ID_EX::get_mem_read()
{
    return mem_read;
}
bool ID_EX::set_mem_read(int64_t ins)
{
    if (set_opcode(ins) == 0x20)
    {
        mem_read = 1;
        return mem_read;
    }
    else
    {
        mem_read = 0;
        return mem_read;
    }
    return 0;
}

bool ID_EX::get_mem_write()
{
    return mem_write;
}
bool ID_EX::set_mem_write(int64_t ins)
{
    if (set_opcode(ins) == 0x28)
    {
        mem_write = 1;
        return mem_write;
    }
    else
    {
        mem_write = 0;
        return mem_write;
    }
    return 0;
}

bool ID_EX::get_reg_write()
{
    return reg_write;
}
bool ID_EX::set_reg_write(int64_t ins)
{
    if (set_opcode(ins) == 0x28)
    {
        reg_write = 0;
        return reg_write;
    }
    else
    {
        reg_write = 1;
        return reg_write;
    }
    return 0;
}

string ID_EX::get_mem2reg()
{
    return mem2reg;
}
string ID_EX::set_mem2reg(int64_t ins)
{
    if (set_opcode(ins) == 0)
    {
        mem2reg = "0";
        return mem2reg;
    }
    else if (set_opcode(ins) == 0x20)
    {
        mem2reg = "1";
        return mem2reg;
    }
    else if (set_opcode(ins) == 0x28)
    {
        mem2reg = "X";
        return mem2reg;
    }
    return 0;
}

void ID_EX::print(){
    cout << "Control: RegDest = " << reg_dst << ", " << "ALUSrc = " << ALU_src << ", "
    << "ALUOp = " << dec << setw(2)<< ALU_op << "," << endl;
    cout << "MemRead = " << mem_read << ", " << "MemWrite = " << mem_write << ", "
    << "Branch = 0" << "," << endl;
    cout << "MemToReg = " << mem2reg << ", " << "RegWrite = " << reg_write << endl;
    cout << "ReadReg1Value = " << hex << readreg1 << ", "
    << "ReadReg2Value = " << hex << readreg2 << "," << endl;
    cout << "SEOffset = " << offset_code << "," << std::endl;
    cout << "WriteReg_20_16 = " << dec << writereg_20_16 << ", "
    << "WriteReg_15_11 = " << dec << writereg_15_11 << "," << endl;
    cout << "Function = " << func_code << endl;
    //std::cout << "opcode = " << opcode << std::endl;
    //std::cout << "offset = " << std::dec <<offset << std::endl;
}



