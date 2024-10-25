# Total Serialism

Generate Customizable Total Serial Style sheet music

### Features
- Generates Total Serial pdf sheet music in seconds
- Customizable Features:
    - Choice of 15 different instruments
    - Set unique or random Row numbers and types for all instruments
    - Set a dynamic for each row
    - Pieces can be an arbitrary length
    - Set Tempo
    - Set Time Signature
    - Set piece title and composer
    - Export Parts

### Requirements:
  - Cmake
  - C++ Compiler with C++ 20 support
  - Python3 with PyQt6 installed
  - Lilypond Compiler (www.lilypond.org)

### Build: 

`sh setup.sh`

### Run: 

`python3 main.py` or `./run`

If you don't have pyqt installed, you can specify a seed for randomness with 

`sh score.sh <seed>`.

Alternatively, you can specify an input file and output filename. The input file must be in the same 
form as below or it will not work. Then run 

`sh score.sh <output_filename> <input_filename>`

### Tests: 

There are a 3 non rigorous unit tests written using google test. They can be run with the script

`sh unitTests.sh`

There is also a longer fuzz testing script. Fuzz testing leverages the lilypond compiler's error messages:

`sh fuzzTest.sh <numTests> <max_parallel_tests>`

It checks if there are no errors or warnings from the lilypond compiler. The lilypond compiler is slow and this test takes some time to run. 
The number of tests defaults to 10, max parallel tests defaults to 4.

### Release: 
- Release 1.0 code freeze: 10/24/24

### Roadmap
- Grand Plans for 2.0
    - Export Midi files
    - Gui could be improved
- No Tickets have been written (8/24/24)
- Email requests to `keymckeyface@gmail.com`


### Notes:

Input Files are in this format. It's typically easier to use the gui if you have pyqt installed. 
```
11 10 9 8 7 6 5 4 3 2 1 0 // Pitch P0 Row
0 1 2 3 4 5 6 7 8 9 10 11 // Rhythm P0 Row
7 8 9 3 0 11 6 10 4 5 1 2 // Articulation P0 Row
120 // Tempo
9/8 // Time Signature
Title // Title
Composer Name // Composer
14 // Number of rows in the piece, aka piece length
3 // Number of instruments
trombone // Instrument 1 name
1 0 10 1 3 2 1 1 3 10 7 10 6 5 // Row Numbers
RI I RI RI I R I R R RI RI R R R // Row Types
7 1 9 5 2 7 7 6 6 0 8 8 6 1 // Row Dynamics
violin
4 0 10 10 8 0 11 4 2 1 0 0 6 9 // Row Numbers
P RI R RI RI I I RI RI R RI RI RI R // Row Types
5 2 1 7 9 8 10 6 2 5 5 8 7 0 // Row Dynamics
bass
0 8 0 10 0 7 4 11 10 4 0 10 6 6 // Row Numbers
R RI P RI RI P R P R R R P RI R // Row Types
9 5 1 6 10 8 0 10 10 5 0 6 6 6 // Row Numbers
```

#### Available Instruments:

- violin
- viola
- cello
- bass
- oboe
- bassoon
- clarinet
- piccolo
- flute
- trombone
- trumpet
- frenchhorn
- tuba
- piano
- harp

 Instruments must be spelled in this specific spelling in the instrument input files: 

#### Available Time Signatures: 
- 4/4 (Default)
- 1/4
- 3/8
- 2/4
- 5/8
- 6/8
- 3/4
- 7/8
- 9/8
- 5/4
- 11/8
- 12/8
- 6/4
- 3/2
- 13/8
- 7/4
- 15/8
