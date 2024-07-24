# Total Serialism

This repo contains code for a Total Serial Music generator

 ### Requirements:
  - Cmake
  - Python3 with PyQt6
  - Lilypond Compiler (www.lilypond.org)

### Build: 

`mkdir build && cd build`
`cmake ..`


### Run: 

`python3 main.py` or `./run`

If you don't have pyqt installed, you can specify a seed for randomness with 

`sh score.sh <seed>`.

Alternatively, you can specify an input file and output filename. The input file must be in the same 
form as below or it will not work. Then run 

`sh score.sh <output_filename>, <input_filename>`

### Tests: 

There are a 3 non rigorous unit tests written using google test. They can be run with the script

`sh unitTests.sh`

There is also a longer fuzz testing script. Fuzz testing leverages the lilypond compiler's error messages:

`sh fuzzTest.sh <numTests>`

It checks if there are no errors or warnings from the lilypond compiler. The lilypond compiler is slow and this test takes some time to run. 
The number of tests defaults to 10. 


### Notes:

Input Files are in the form. It's typically easier to use the gui if you have pyqt installed. 
```
0 1 2 3 4 5 6 7 8 9 10 11 // Pitch P0 Row
0 1 2 3 4 5 6 7 8 9 10 11 // Rhythm P0 Row
0 1 2 3 4 5 6 7 8 9 10 11 // Articulation P0 Row
0 1 2 3 4 5 6 7 8 9 10 11 // Right Hand Row numbers (P5, this row is he 5)
0 1 2 3 4 5 6 7 8 9 10 11 // Left hand row numbers
0 1 2 3 4 5 6 7 8 9 10 11 // Dynamics P0 Row
P R P R P R P R P R P R // Left hand Row Type
I RI I RI I RI I RI I RI I RI // Right hand row type
140 // Tempo
12/8 // Time Signature
TEST // Title
The_Algorithm // Composer. 
```


### Roadmap: 
- Allow for longer pieces/custom piece length
- Multiple Instruments
- gui Help screen
- Dialog box on incorrect gui input
- Midi?
