# Total Serialism

This repo contains code for a Total Serial Music generator

 ### Requirements:
  - Cmake
  - Python3 with PyQt6
  - Lilypond Compiler (www.lilypond.org)

### Build: 

`mkdir build && cd build`
`cmake ..`


### Run: `python3 main.py`

There are 2 non rigorous test suites: 
`build/analysisMatrix-test` and `build/serialismGenerator-test`

### Notes:

All music is in 13/16, mostly to make sure the time signature works out.

Input Files are in the form 

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
TEST // Title
The_Algorithm // Composer. Must be one word (will change...)
```


### Roadmap: 
- Allow for longer pieces
- Time signature other than 13/16
- Better GUI (Planned and drawn, not implemented)
- Midi?
