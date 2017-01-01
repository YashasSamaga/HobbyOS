@echo off
echo ======================================================================================
color 2B
echo System Constructor 
echo Lindus Kernel Driver Builder
echo --------------------------------------------------------------------------------------
pause

echo --------------------------------------------------------------------------------------

..\..\..\Tools\gcc -Wall -O  -finline-functions -fno-builtin -I./../include -c -o ../Output/screen.o ../drivers/textmode/screen.c

echo --------------------------------------------------------------------------------------


pause