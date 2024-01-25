
//  main.cpp

#include <iostream>
#include "Pipeline.hpp"

void pipeline_simulation(int64_t *);

int main(){

    int64_t InstructionCache[12] = {0xa1020000, 0x810AFFFC,0x00831820,0x01263820,
                                0x01224820, 0x81180000,0x81510010,0x00624022,
                                0x00000000,0x00000000, 0x00000000,0x00000000};
    pipeline_simulation(InstructionCache);
    return 0;
}


void pipeline_simulation(int64_t *insarray){

    Pipeline pipeline;
    int64_t instruction;

    for(int i = 0; i < 12; i++)
    {
        cout << "\n Clock Cycle " << dec << (i+1) << endl;
        std::cout
        << "(Before we copy the write side of pipeline register to the read side) \n" <<
        std::endl;

        instruction = insarray[i];
        pipeline.IF_stage(instruction);
        pipeline.ID_stage();
        pipeline.EX_stage();
        pipeline.MEM_stage();
        pipeline.WB_stage();
        pipeline.Print_out_everything();
        pipeline.Copy_write_to_read();

    }
}

