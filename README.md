# Total Serialism

Total-Serialism is a containerized app to generate Customizable Total Serial Style sheet music. 

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

### Build Requirements:
  - C++ compiler with C++20 support (specifically `std::format`)

### Build: 

Python gui: 
`pip install .`

C++ cli and tests: 
```
mkdir build
cd build
cmake -DTS_DO_TESTS ..
cmake --build . --parallel 10
```

### Run: 

Run via gui: 

`./run`

Run via cli:

- Run with seeded randomness:  `sh score.sh <options>`
- Run with specified input and output file: `sh score.sh <output_filename> <input_filename>`
- Each can accept a `-p` flag to create individual parts

### Tests: 

Tests can be built with `cmake -DTS_DO_TESTS=ON ..` in the configure command. 
The tests are in the `tests` folder in the build directory and can be run with `ctest tests -j5`

### Release: 
- Release 1.0 code freeze: 10/24/24
- Release 1.1.0 code freeze: 5/26/25
- Release 1.2.0: 6/30/26

### Roadmap
- Grand Plans for 2.0
    - Export Midi files
    - Gui could be improved
    - App should be able to be run from a pre-built and pushed docker image. 
- No Tickets have been written (5/26/25)
- Email requests to `keymckeyface@gmail.com`


### Notes:

Input Files are in this format. It's typically easier to use the gui if you have PyQt6 installed. 
```
11 10 9 8 7 6 5 4 3 2 1 0 // Pitch P0 Row
0 1 2 3 4 5 6 7 8 9 10 11 // Rhythm P0 Row
7 8 9 3 0 11 6 10 4 5 1 2 // Articulation P0 Row
120 // Tempo
9/8 // Time Signature
Title // Title
Composer Name // Composer
14 // Number of rows in the piece, (piece length)
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

Instruments must be spelled in this specific spelling in the instrument input files

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
