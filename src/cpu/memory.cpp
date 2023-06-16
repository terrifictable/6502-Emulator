#include "cpu.hpp"

#include <string.h>

byte Memory::operator[](u32 addr) {
    if (addr > MAX_MEM-1) {
        return -1;
    }
    return this->data[addr];
}


void Memory::init() {
    memset(this->data, 0, this->MAX_MEM);
}

void Memory::write_word(s32 &cycles, word val, u32 addr) {
    this->data[addr]   = val & 0xff;
    this->data[addr+1] = (val >> 8) & 0xff;
    cycles -= 2;
}

