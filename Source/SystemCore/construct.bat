@echo off
echo ======================================================================================
color 2B
echo System Constructor 
echo Lindus Kernel
echo --------------------------------------------------------------------------------------
pause

echo --------------------------------------------------------------------------------------
@echo on

..\..\Tools\nasm -f aout -o Output\entry.o entry.asm

echo --------------------------------------------------------------------------------------

..\..\Tools\gcc -Wall -O  -finline-functions -fno-builtin -I./include -c -o Output\init.o init.c


echo --------------------------------------------------------------------------------------

..\..\Tools\ld -T link.ld -o kernel.bin Output/entry.o Output/init.o Output/screen.o Output/string.o

pause