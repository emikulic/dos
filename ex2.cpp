// ex2.cpp: smaller MOVs
// Copyright (c) 2024 Emil Mikulic

void exit1() {
    asm volatile (
            "movw %0, %%ax\n"
            "int $0x21"
            : // no outputs
            : // no inputs
            "i" (0x4C00)  // AH = 4Ch - exit to dos
                          // AL = 00h - the exit code
            : "ax" // clobbers AX
            );
    __builtin_unreachable();
}

void exit2() {
    asm volatile (
            "int $0x21"  // Simpler - no MOV.
            : // no outputs
            : "a" (0x4C00)  // Make the compiler populate AX!
            : // no clobbers, the compiler knows it clobbered AX
            );
    __builtin_unreachable();
}

// $ clang++ -c -Os -nostdlib -m16 -march=i386 -fno-exceptions -ffreestanding ex2.cpp
// $ objdump -m i8086 -M intel -d ex2.o
// 
// 00000000 <_Z5exit1v>:
//    0:	b8 00 4c             	mov    ax,0x4c00
//    3:	cd 21                	int    0x21
// 
// 00000005 <_Z5exit2v>:
//    5:	66 b8 00 4c 00 00    	mov    eax,0x4c00 <-- twice the size
//    b:	cd 21                	int    0x21

// vim:set sts=4 ts=4 sw=4 et tw=80:
