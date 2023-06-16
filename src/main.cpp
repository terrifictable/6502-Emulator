#include <iostream>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "cpu/cpu.hpp"

int main(unused int argc, unused char *argv[]) {
    Memory mem;
    CPU cpu;
 
    cpu.reset(mem);

    /* start - inline program */
    mem.data[0xfffc] = CPU::INST_JSR;
    mem.data[0xfffd] = 0x42;
    mem.data[0xfffe] = 0x24;
    mem.data[0x2442] = CPU::INST_LDA_IM;
    mem.data[0x2443] = 0x84;
    /* end - inline program */

    cpu.exec(11, mem);

    if (argc > 1 && strcmp(argv[1], "dbg") == 0) {
        printf("\n\n");
        dbg_cpu(cpu, mem);
    }

    if (cpu.err != nullptr) {
        printf("Emulation Failed with error: %s\n", cpu.err);
    }

    return 0;
}

