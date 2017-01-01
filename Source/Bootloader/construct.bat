@echo off
color 2B
echo ===============================================================================
echo System Build Script
echo Colour = 2B(Green\Black)
echo ===============================================================================

pause

@echo on
..\..\Utilities\Tools\nasm -f bin ..\..\Source\Bootloader\Bootsector\bootsec.asm -o ..\..\Source\Bootloader\Output\bootsec.bin

..\..\Utilities\Tools\nasm -f bin ..\..\Source\Bootloader\Loader\bootloader.asm -o ..\..\Source\Bootloader\Output\bootloader.bin

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin  -c -o main.o main.c

copy Output\bootloader.bin A:\loader.bin
copy Output\kernel.bin A:\kernel.bin
partcopy Output\bootsec.bin 0 200 -f0


@echo off
echo ===============================================================================
echo Constrution Done

pause
