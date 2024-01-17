# Building a COM program for MS-DOS

A `COM` file is an unstructured memory image that gets loaded into memory at
`0192h:0100h` and then JMP'd into.  Meaning whatever is at the start of the COM
file is code that gets immediately executed.

The three segments `CS`, `DS`, and `ES` are all set to `0192h`.

## The DOS Interrupt

We need to call into DOS to do things like printing to stdout or exiting the
program. To do this, put the number of the syscall into the AH register, put the
arguments into other registers, then do `int 21h` to call into the OS.

You'll need to look up the numbers and registers in an [interrupt
reference](https://www.ctyme.com/intr/int-21.htm).

## Assembler syntax

I prefer the Intel syntax, so I ask for disassembly in Intel, but I use AT&T
syntax in inline assembler blocks in the code because I found it easier than
fighting with the compiler.

## Hello world

[ex1.cpp] shows:
  * Printing to stdout and exiting back to DOS.
  * Functions calling each other.

The linker script [com.ld] shows:
  * How to put `_start` at the correct location.

Compile and link:

```shell
clang++ -c -Os -nostdlib -m16 -march=i386 -fno-exceptions -ffreestanding ex1.cpp
ld --script com.ld -melf_i386 -o ex1.com ex1.o
```

Disassemble the object file with the correct machine (`-m i8086`) otherwise
instructions will be decoded incorrectly, e.g. `int 21h` becomes part of an
immediate loaded into `edx`:

```shell
objdump -m i8086 -M intel -d ex1.o
```

Disassemble the `COM` file to see the final product:

```shell
objdump -m i8086 -M intel -D -b binary ex1.com
```

List functions by size:

```shell
nm --print-size --radix=d --size-sort --demangle ex1.o
```

vim:set tw=80:
