//
//  Mem_WB.hpp
//

#ifndef Mem_WB_hpp
#define Mem_WB_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

class Mem_WB {
public:

    Mem_WB();

    string get_lw_val();
    int get_ALU_result_mm();
    string get_write_regnum_mm();
    void set_lw_val(int);
    int set_ALU_result_mm(int);
    string set_write_regnum_mm(int);
    string set_write_regnum_mm(string);
    string get_mem2reg_mm();
    bool get_reg_write_mm();
    string set_mem2reg_mm(string);
    bool set_reg_write_mm(bool);

    void print();

private:

    string lw_val = "0";
    int ALU_result_mm = 0x00;
    string write_regnum_mm = "0";
    string mem2reg_mm = "0";
    bool reg_write_mm = 0;
};


#endif /* Mem_WB_hpp */
