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
    mem.data[0xfffc] = CPU::INST_LDA_IM;
    mem.data[0xfffd] = 0x42;
    /* end - inline program */

    cpu.exec(3, mem);

    if (argc > 1 && strcmp(argv[1], "dbg") == 0) {
        printf("\n\n");
        dbg_cpu(cpu, mem);
    }

    return 0;
}

