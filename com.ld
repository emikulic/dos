OUTPUT_FORMAT(binary)
ENTRY(_start)
SECTIONS
{
  . = 0x100;
  .text :
  {
    *(.start)
    *(.text*)
  }
  /DISCARD/ :
  {
    *(.note*);
    *(.comment*);
    *(.llvm*);
  }
  /* this is correct despite not enumerating e.g. data sections above */
  _heap = ALIGN(4);
}
