#include "cpu.hpp"


#include "common.h"
#include <stdio.h>


/* initialization sequence */
void CPU::reset(Memory &memory) {
    this->pc = 0xfffc;
    this->sp = 0x0100;
    
    this->status.c = 0;
    this->status.z = 0;
    this->status.i = 0;
    this->status.d = 0;
    this->status.b = 0;
    this->status.v = 0;
    this->status.n = 0;
    
    this->ra = 0;
    this->rx = 0;
    this->ry = 0;
    
    memory.init();
}

byte CPU::fetch_byte(s32 &cycles, Memory &mem) {
    u32 data = mem[this->pc];
    this->pc++;
    cycles--;
    return data;
}

byte CPU::read_byte(s32 &cycles, byte addr, Memory &mem) {
    cycles--;
    return mem[addr];
}

void CPU::exec(s32 cycles, Memory &mem) {
    do {
        byte inst = fetch_byte(cycles, mem); 
         
        // printf("Cycles: %d\n", cycles < 0);
        // printf("PC: %x\n", this->pc);
        // printf("SP: %x\n", this->sp);
        // printf("MEM: %x %x %x %x %x\n", mem[this->pc-2], mem[this->pc-1], mem[this->pc], mem[this->pc+1], mem[this->pc+2]);
        // printf("INST: %x\n", inst);
        
        switch (inst) {
            case INST_NOP: 
                {
                    --cycles;
                } break;

            case INST_LDA_IM: 
                {
                    byte val = fetch_byte(cycles, mem);
                    this->ra = val;
                    this->status.z = (this->ra == 0);
                    this->status.n = (this->ra & 0b10000000) > 0;
                } break;

            default:
                {
                    info("Unknown instruction byte: %x", inst);
                } break;

        }

        --cycles;
    } while (cycles > 0);
}



void dbg_cpu(CPU &cpu, Memory &mem) {
    msg("PC: 0x%.4x", cpu.pc);
    msg("SP: 0x%.4x", cpu.sp);
    
    msg("\n%s Registers %s", "==", "==");
    msg("\tA: 0x%.2x", cpu.ra);
    msg("\tX: 0x%.2x", cpu.rx);
    msg("\tY: 0x%.2x", cpu.ry);
    
    msg("\n%s Flags %s", "==", "==");
    msg("\tCarry     flag: %d", cpu.status.c);
    msg("\tZero      flag: %d", cpu.status.z);
    msg("\tInterrupt flag: %d", cpu.status.i);
    msg("\tDecimal   flag: %d", cpu.status.d);
    msg("\tBreak     flag: %d", cpu.status.b);
    msg("\tOverflow  flag: %d", cpu.status.v);
    msg("\tNegative  flag: %d", cpu.status.n);


    msg("\n%s Memory %s", "==", "==");
    printf("\tSP..SP+2:\n");
    printf("\t\t0x%.4x  ", cpu.sp);
    for (u32 i=0; i < 3 && i < MAX_LOOP; ++i) {
        if (cpu.sp+i > mem.MAX_MEM-1) {
            break;
        }
        printf("%.2x ", mem[cpu.sp+i]);
    }
    printf("\n");

    printf("\tPC..PC+2: \n");
    printf("\t\t0x%.4x  ", cpu.pc);
    for (u32 i=0; i < 3 && i < MAX_LOOP; ++i) {
        if (cpu.pc+i > mem.MAX_MEM-1) {
            break;
        }
        printf("%.2x ", mem[cpu.pc+i]);
    }
    printf("\n");
}

