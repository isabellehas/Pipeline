//
//  Pipeline.cpp
//

#include "Pipeline.hpp"


Pipeline::Pipeline(){
    // initialize pipeline & registers
    Initialize();
};

void Pipeline::IF_stage(int64_t ins)
{
    // fetch instructions
    IF_ID_Write.set_instruction(ins);
}

void Pipeline::ID_stage()
{
    int64_t ins = IF_ID_Read.get_instruction();

    // for instruction decode
    ID_EX_Write.set_opcode(ins);
    ID_EX_Write.set_offset(ins);
    ID_EX_Write.set_offset_code(ins);
    ID_EX_Write.set_readreg_1(ins, Regs);
    ID_EX_Write.set_readreg_2(ins, Regs);
    ID_EX_Write.set_writereg_15_11(ins);
    ID_EX_Write.set_writereg_20_16(ins);
    ID_EX_Write.set_function_code(ins);
    ID_EX_Write.setinstruction_ex(ins);

    // for control bits
    ID_EX_Write.set_reg_dst(ins);
    ID_EX_Write.set_ALU_op(ins);
    ID_EX_Write.set_ALU_src(ins);
    ID_EX_Write.set_mem_read(ins);
    ID_EX_Write.set_mem_write(ins);
    ID_EX_Write.set_reg_write(ins);
    ID_EX_Write.set_mem2reg(ins);

}

void Pipeline::EX_stage()
{
    // perform instructions
    EX_Mem_Write.set_mem_read_ex(ID_EX_Read.get_mem_read());
    EX_Mem_Write.set_mem_write_ex(ID_EX_Read.get_mem_write());
    EX_Mem_Write.set_reg_write_ex(ID_EX_Read.get_reg_write());
    EX_Mem_Write.set_mem2reg_ex(ID_EX_Read.get_mem2reg());
    EX_Mem_Write.set_ALU_result(ALU_res_ex());
    EX_Mem_Write.set_sw_value(ID_EX_Read.get_readreg_2());
    EX_Mem_Write.set_write_regnum(w_regnum_ex());
        
}

// set ALU result in EX stage
int Pipeline::ALU_res_ex()
{
    int ALURes;
    if(ID_EX_Read.get_function_code() == "20"){
        ALURes = ID_EX_Read.get_readreg_1() + ID_EX_Read.get_readreg_2();
    }  //add
    else if(ID_EX_Read.get_function_code() == "22"){
        ALURes = ID_EX_Read.get_readreg_1() - ID_EX_Read.get_readreg_2();
    } // sub
    else if(ID_EX_Read.get_ALU_src() == 1){
        ALURes = ID_EX_Read.get_readreg_1() + ID_EX_Read.get_offset();
    } // i type
    else {
        ALURes = 0;
    }
    return ALURes;
}

//set reg# for EX stage
int Pipeline::w_regnum_ex(){
    int regnum;
    if(ID_EX_Read.get_reg_dst() == "1"){
        regnum = ID_EX_Read.get_writereg_15_11();
    }//R type
    else if(ID_EX_Read.get_reg_dst() == "0"){
        regnum = ID_EX_Read.get_writereg_20_16();
    }
    else {
        regnum = 0;
    }// lw

    return regnum;
}

void Pipeline::MEM_stage()
{
    Mem_WB_Write.set_mem2reg_mm(EX_Mem_Read.get_mem2reg_ex());
    Mem_WB_Write.set_reg_write_mm(EX_Mem_Read.get_reg_write_ex());
    Mem_WB_Write.set_lw_val(LWval());
    Mem_WB_Write.set_ALU_result_mm(EX_Mem_Read.get_ALU_result());
    Mem_WB_Write.set_write_regnum_mm(EX_Mem_Read.get_write_regnum());
    // for sw, update main memory
    if(EX_Mem_Read.get_mem2reg_ex() == "X"){
        Main_Mem[Mem_WB_Write.get_ALU_result_mm()] = EX_Mem_Read.get_sw_value();
    }
}

int Pipeline::LWval(){
    int lwval = 0x00;
    if(EX_Mem_Read.get_mem_read_ex() == 1 && EX_Mem_Read.get_mem_write_ex() == 0)
    {
        lwval = Main_Mem[Mem_WB_Write.get_ALU_result_mm()];
    }
    return lwval;
}

void Pipeline::WB_stage()
{
    int reg_val = 0;
    int n;
    string nstr;
    // calculate what to write in registers
    if(Mem_WB_Read.get_mem2reg_mm() == "0") // R type
    {
        reg_val = Mem_WB_Read.get_ALU_result_mm();
    }
    else if(Mem_WB_Read.get_mem2reg_mm() == "1") //sw
    {
        string reg_val_str;
        reg_val_str = Mem_WB_Read.get_lw_val();
        reg_val = atoi(reg_val_str.c_str());
    }
    
    nstr = Mem_WB_Read.get_write_regnum_mm();
    n = atoi(nstr.c_str());
    Regs[n] = reg_val;
}

void Pipeline::Print_out_everything()
{
    //IF_ID
    cout << "IF_ID Write (written to by the IF stage) \n";
    IF_ID_Write.print();
    cout << "\nIF_ID Read (read by the ID stage) \n";
    IF_ID_Read.print();

    //ID_EX
    cout << "\nID_EX Write (written to by the ID stage) \n";
    int64_t inst_w = ID_EX_Write.getinstruction_ex();
    if(inst_w == 0)
    {
        cout << "NOP" << endl;
    } // for nop
    else
    {
        ID_EX_Write.print();
    }
    
    cout << "\nID_EX Read (read by the EX stage) \n";
    int64_t inst_r = ID_EX_Read.getinstruction_ex();
    if(inst_r == 0)
    {
        cout << "NOP" << endl;
    } // nop
    else
    {
        ID_EX_Read.print();
    }

    // EX_Mem
    cout << "\nEX_MEM Write (written to by the EX stage) \n";
    int ALU_w = EX_Mem_Write.get_ALU_result();
    if(ALU_w == 0)
    {
        cout << "NOP" << endl;
    } //nop
    else
    {
        EX_Mem_Write.print();
    }
    
    cout << "\nEX_MEM Read (read by the Mem stage) \n";
    int ALU_r = EX_Mem_Read.get_ALU_result();
    if(ALU_r == 0)
    {
        cout << "NOP" << endl;
    }
    else
    {
        EX_Mem_Read.print();
    }

    //Mem_WB
    cout << "\nMEM_WB Write (written to by the Mem stage) \n";
    int64_t ALU_W = Mem_WB_Write.get_ALU_result_mm();
    if(ALU_W == 0)
    {
        cout << "NOP" << endl;
    }
    else
    {
        Mem_WB_Write.print();
    }
    //Mem_WB_Write.print();
    cout << "\nMEM_WB Read (read by the WB stage) \n";
    int64_t ALU_R = Mem_WB_Read.get_ALU_result_mm();
    if(ALU_R == 0)
    {
        cout << "NOP" << endl;
    }
    else
    {
        Mem_WB_Read.print();
    }
    
    // 32 registers
    cout << "\n32 Registers " <<endl;
    for (int i = 0; i < 32; i++){
        cout << "Reg[" << i << "] = 0x" << hex << Regs[i] << endl;
    }
}

void Pipeline::Copy_write_to_read()
{
    IF_ID_Read = IF_ID_Write;
    ID_EX_Read = ID_EX_Write;
    EX_Mem_Read = EX_Mem_Write;
    Mem_WB_Read = Mem_WB_Write;
}


void Pipeline::Initialize()
{
   
    short j = 0;
    Main_Mem[0] = 0x00;
    for(int i = 0; i < 1024; i++){
        if (j <= 0xff) {
            Main_Mem[i] = j;
            j++;
        }
        else {
            j = 0;
            Main_Mem[i] = j;
            j++;
        }
     
        
        /*
        for(short j = 0; j <= 0xFF; j++){
            Main_Mem[i] = j;
        }
         */
    }
    
    Regs[0] = 0;
    for(int m = 1; m < 32; m++){
        Regs[m] = 0x100 + m ;
        //n = n+1;
    }
}
