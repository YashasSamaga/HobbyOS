@echo off
echo ======================================================================================
color 2B
echo System Constructor 
echo Lindus Kernel Libary Builder
echo --------------------------------------------------------------------------------------
pause

echo --------------------------------------------------------------------------------------
@echo on
..\..\..\Tools\gcc -Wall -O  -finline-functions -fno-builtin -I./../include -c -o ..\Output\string.o ../lib/string.c

@echo off
echo --------------------------------------------------------------------------------------


pause