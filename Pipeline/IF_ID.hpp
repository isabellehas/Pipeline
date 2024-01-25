//
//  IF_ID.hpp


#ifndef IF_ID_hpp
#define IF_ID_hpp


#include <stdio.h>
using namespace std;


class IF_ID {
public:
    IF_ID();
    int64_t get_instruction();
    int64_t set_instruction(int64_t ins);
    void print()const;
private:
    int64_t instruction = 0x00000000;
};


#endif /* IF_ID_hpp */
