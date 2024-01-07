#include "cpu.hpp"


#include "common.h"
#include <stdio.h>
#include <stdlib.h>


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

void CPU::cycles_guard(s32 &cycles, s32 decr) {
    if (cycles < decr) {
        this->err = (char*)malloc(1024 * sizeof(char));
        sprintf(this->err, "Not Enough Cycles at cycle: %d with decrement: %d", cycles, decr);
    }

    cycles -= decr;
}

byte CPU::fetch_byte(s32 &cycles, Memory &mem) {
    u32 data = mem[this->pc];
    this->pc++;

    cycles_guard(cycles, 1);
    return data;
}

byte CPU::read_byte(s32 &cycles, byte addr, Memory &mem) {
    cycles_guard(cycles, 1);
    return mem[addr];
}

word CPU::fetch_word(s32 &cycles, Memory &mem) {
    word data = mem[this->pc];
    this->pc++;

    data |= (mem[this->pc] << 8);
    this->pc++;

    cycles_guard(cycles, 2);
    return data;
}



void CPU::load_register(byte &reg, byte value) {
    reg = value;
    this->status.z = (reg == 0);
    this->status.n = (reg & 0b100000000) > 0; // ...byte is unsigned, so negative should not be possible
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
            case INST_NOP: {
                    cycles_guard(cycles, 1);
                } break;

            /* LDA */
            case INST_LDA_IM: {
                    byte val = fetch_byte(cycles, mem);
                    load_register(this->ra, val);
                } break;

            case INST_LDA_ZP: {
                    byte zp_addr = fetch_byte(cycles, mem);
                    byte val = read_byte(cycles, zp_addr, mem);
                    load_register(this->ra, val);
                } break;

            case INST_LDA_ZPX: {
                    byte zp_addr = fetch_byte(cycles, mem);
                    zp_addr += this->rx;
                    cycles_guard(cycles, 1);

                    byte val = read_byte(cycles, zp_addr, mem);
                    load_register(this->ra, val);
                } break;
            /* LDA */

            /* LDX */
            case INST_LDX_IM: {
                    byte val = fetch_byte(cycles, mem);
                    load_register(this->rx, val);
                } break;

            case INST_LDX_ZP: {
                    byte zp_addr = fetch_byte(cycles, mem);
                    byte val = read_byte(cycles, zp_addr, mem);
                    load_register(this->rx, val);
                } break;

            case INST_LDX_ZPY: {
                    byte zp_addr = fetch_byte(cycles, mem);
                    zp_addr += this->ry;
                    cycles_guard(cycles, 1);

                    byte val = read_byte(cycles, zp_addr, mem);
                    load_register(this->rx, val);
                } break;
            /* LDX */

            /* LDY */
            case INST_LDY_IM: {
                    byte val = fetch_byte(cycles, mem);
                    load_register(this->ry, val);
                } break;

            case INST_LDY_ZP: {
                    byte zp_addr = fetch_byte(cycles, mem);
                    byte val = read_byte(cycles, zp_addr, mem);
                    load_register(this->ry, val);
                } break;

            case INST_LDY_ZPX: {
                    byte zp_addr = fetch_byte(cycles, mem);
                    zp_addr += this->rx;
                    cycles_guard(cycles, 1);

                    byte val = read_byte(cycles, zp_addr, mem);
                    load_register(this->ry, val);
                } break;

            /* LDX */

            case INST_JSR: {
                    word jp_addr = fetch_word(cycles, mem);
                    mem.write_word(cycles, this->pc-1, this->sp);
                    this->pc = jp_addr;

                    cycles_guard(cycles, 2);
                } break;

            default: {
                    info("Unknown instruction byte: %x", inst);
                } break;
        }

        cycles_guard(cycles, 1);
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


    static const int MAX_LOOP = 1000000;

    msg("\n%s Memory %s", "==", "==");
    printf("\tSP-1..SP+1:\n");
    printf("\t\t0x%.4x:  ", cpu.sp);
    for (u32 i=0; i < 3 && i < MAX_LOOP; ++i) {
        if (cpu.sp-1+i > mem.MAX_MEM-1) {
            break;
        }
        printf("%.2x ", mem[cpu.sp-1+i]);
    }
    printf("\n");

    printf("\tPC-1..PC+1: \n");
    printf("\t\t0x%.4x:  ", cpu.pc);
    for (u32 i=0; i < 3 && i < MAX_LOOP; ++i) {
        if (cpu.pc-1+i > mem.MAX_MEM-1) {
            break;
        }
        printf("%.2x ", mem[cpu.pc-1+i]);
    }
    printf("\n");
}

