//
//  Pipeline.hpp

#ifndef Pipeline_hpp
#define Pipeline_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include "IF_ID.hpp"
#include "ID_EX.hpp"
#include "EX_Mem.hpp"
#include "Mem_WB.hpp"


class Pipeline
{
public:
    Pipeline();

    void IF_stage(int64_t);
    void ID_stage();
    void EX_stage();
    void MEM_stage();
    void WB_stage();
    void Print_out_everything();
    void Copy_write_to_read();
    void Initialize();
    int ALU_res_ex();
    int w_regnum_ex();
    int LWval();
    int reg_value();

private:
    int Regs[32];
    int Main_Mem[1024];
    IF_ID IF_ID_Read;
    IF_ID IF_ID_Write;
    ID_EX ID_EX_Read;
    ID_EX ID_EX_Write;
    EX_Mem EX_Mem_Read;
    EX_Mem EX_Mem_Write;
    Mem_WB Mem_WB_Read;
    Mem_WB Mem_WB_Write;
};


#endif /* Pipeline_hpp */
