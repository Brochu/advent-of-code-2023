@echo off

.\compile.bat %1 & type .\inputs\day%1.txt | .\AoC2023.exe
