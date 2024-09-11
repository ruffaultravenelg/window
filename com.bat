@echo off
gcc "test\%1.c" window.c -o bin/prog -lgdi32