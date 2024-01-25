//
//  ID_EX.hpp


#ifndef ID_EX_hpp
#define ID_EX_hpp

#include <stdio.h>
#include <iostream>
using namespace std;


class ID_EX {
public:
    ID_EX();

    int64_t getinstruction_ex();
    int64_t setinstruction_ex(int64_t);
    
    // Get Function
    int get_readreg_1();
    int get_readreg_2();
    short get_offset();
    string get_offset_code();
    int get_writereg_20_16();
    int get_writereg_15_11();
    int get_opcode();
    int get_function();
    string get_function_code();

    // Set Functions
    int set_readreg_1(int64_t ins, int reg[]);
    int set_readreg_2(int64_t ins, int reg[]);
    void set_offset(int64_t ins);
    string set_offset_code(int64_t ins);
    int set_writereg_20_16(int64_t ins);
    int set_writereg_15_11(int64_t ins);
    int set_opcode(int64_t ins);
    int set_function(int64_t ins);
    string set_function_code(int64_t ins);

    // Control bit get and set
    string get_reg_dst();
    int get_ALU_op();
    bool get_ALU_src();
    bool get_mem_read();
    bool get_mem_write();
    bool get_reg_write();
    string get_mem2reg();

    string set_reg_dst(int64_t ins);
    int set_ALU_op(int64_t ins);
    bool set_ALU_src(int64_t ins);
    bool set_mem_read(int64_t ins);
    bool set_mem_write(int64_t ins);
    bool set_reg_write(int64_t ins);
    string set_mem2reg(int64_t ins);

    void print();

private:
    int64_t instruction = 0x00000000;
    int readreg1 = 0;
    int readreg2 = 0;
    int64_t offset = 0;
    string offset_code = "00000000";
    int writereg_20_16 = 0;
    int writereg_15_11 = 0;
    int opcode = 0;
    int function = 0;
    string func_code = "0";
    std::string reg_dst = "0";
    int ALU_op = 0;
    bool ALU_src = 0;
    bool mem_read = 0;
    bool mem_write = 0;
    bool reg_write = 0;
    string mem2reg = "0";
};

#endif /* ID_EX_hpp */
