filename=$1;
lilypond -f pdf -o test test/$filename.ly;
open test/$filename.pdf;
