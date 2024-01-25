//
//  EX_Mem.hpp
//

#ifndef EX_Mem_hpp
#define EX_Mem_hpp

#include <stdio.h>
#include <iostream>
using namespace std;


class EX_Mem {
public:

    EX_Mem();

    // Instructions get and set
    int get_ALU_result();
    int get_sw_value();
    string get_write_regnum();
    void set_ALU_result(int);
    void set_sw_value(int);
    void set_write_regnum(int);

    // Control bits get and set
    bool get_mem_read_ex();
    bool get_mem_write_ex();
    bool get_reg_write_ex();
    string get_mem2reg_ex();
    void set_mem_read_ex(bool);
    void set_mem_write_ex(bool);
    void set_reg_write_ex(bool);
    void set_mem2reg_ex(string);

    void print();
    
private:

    int ALU_result = 0;
    int sw_value = 0;
    string write_regnum = "0";
    bool mem_read_ex = 0;
    bool mem_write_ex = 0;
    bool reg_write_ex = 0;
    string mem2reg_ex = "0";

};
#endif /* EX_Mem_hpp */
