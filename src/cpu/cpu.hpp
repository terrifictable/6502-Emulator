#pragma once


using byte = unsigned char;
using word = unsigned short;

using u32 = unsigned int;
using s32 = signed int;


struct Memory {
    static constexpr u32 MAX_MEM = 1024 * 64;
    byte data[MAX_MEM];

    byte operator[](u32 addr);
    // byte& operator[](u32 addr);
    void write_word(s32 &cycles, word val, u32 addr);

    void init();
};


struct CPU {
    word pc;    // program counter
    word sp;    // stack pointer

    byte ra, rx, ry;    // registers
    
    typedef struct {
        byte c : 1; // carry flag
        byte z : 1; // zero flag
        byte i : 1; // interrupt flag
        byte d : 1; // decimal flag
        byte b : 1; // break flag
        byte v : 1; // overflow flag
        byte n : 1; // negative flag
    } status_t;
    status_t status;    // flags

    char* err = nullptr;


    /* opcodes */
    static constexpr byte 
        /* LDA */
        INST_LDA_IM  = 0xa9,
        INST_LDA_ZP  = 0xa5,
        INST_LDA_ZPX = 0xb5,
        /* LDA */
        
        /* LDX */
        INST_LDX_IM  = 0xa2,
        INST_LDX_ZP  = 0xa6,
        INST_LDX_ZPY = 0xb6,
        /* LDX */
        
        /* LDY */
        INST_LDY_IM  = 0xa0,
        INST_LDY_ZP  = 0xa4,
        INST_LDY_ZPX = 0xb4,
        /* LDY */

        INST_JSR = 0x20,
        
        INST_NOP = 0xea;


    void reset(Memory &memory);
    void exec(s32 cycles, Memory &mem);
    
private:
    void load_register(byte &reg, byte value);

    byte fetch_byte(s32 &cycles, Memory &mem);
    byte read_byte(s32 &cycles, byte addr, Memory &mem);
    
    word fetch_word(s32 &cycles, Memory &mem);

    void cycles_guard(s32 &cycles, s32 decr);
};

void dbg_cpu(CPU &cpu, Memory &mem);
