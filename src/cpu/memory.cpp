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

