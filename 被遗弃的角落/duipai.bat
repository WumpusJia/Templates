@echo off
:again
make > input
a < input > ans.txt
b < input > out.txt
fc ans.txt out.txt > nul
if not errorlevel 1 goto again	
