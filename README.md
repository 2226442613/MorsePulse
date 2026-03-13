# MorsePulse

MorsePulse is a C++ console project that converts text into Morse code and simulates Morse transmission using light-style blinking and audio-style beeps.

## Features
- Encode text to Morse code
- Decode Morse code back to text
- Simulate light blinking timing
- Simulate audio beep timing
- Adjustable words-per-minute style timing
- Clean console interface

## Why this project is useful
This project demonstrates:
- string processing
- maps and dictionaries
- timing with `chrono` and `thread`
- user interface design in the terminal
- modular C++ design

## Build
Using g++:
```bash
g++ -std=c++17 -O2 -o MorsePulse main.cpp
./MorsePulse
