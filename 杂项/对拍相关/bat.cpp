@echo off
g++ -o my.exe my.cpp
g++ -o brute.exe brute.cpp
g++ -o maker.exe maker.cpp
:loop
maker.exe > data.in
my.exe < data.in > my.out
brute.exe < data.in > brute.out
fc my.out brute.out
if not errorlevel 1 goto loop
pause
