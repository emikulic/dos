// ex1.cpp: hello world
// Copyright (c) 2024 Emil Mikulic

// Put everything except _start into an anonymous namespace so that the compiler
// doesn't produce two copies of each function: one inlined into the caller, and
// one standalone one in case another compilation unit needs it (dead code).
namespace {

// Print a string that's terminated with '$'
void print(const char* str) {
    // Marked volatile because of the side-effect of printing the string.
    asm volatile (
            "movb $0x09, %%ah\n"  // AH = 09h - write string to stdout
            "movw %0, %%dx\n"
            "int $0x21"
            : // no outputs
            : // no inputs
            "g" (str)  // DX = ptr to string
            : "ax", "dx" // clobbers
            );
}

int main() {
    print("Hello world!\n$");
    return 0;
}

}

// Put _start into its own section so the linker can place it first.
extern "C" void __attribute__((section(".start"))) _start() {
    main();

    // Call into DOS to exit the program.
    asm volatile (
            "movw %0, %%ax\n"
            "int $0x21"
            : // no outputs
            : // no inputs
            "i" (0x4C00)  // AH = 4Ch - exit to dos
                          // AL = 00h - the exit code
            : "ax" // clobbers AX
            );

    // This makes clang elide a RET but isn't necessary otherwise.
    __builtin_unreachable();
}

// vim:set sts=4 ts=4 sw=4 et tw=80:
