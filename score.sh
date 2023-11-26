filename=$1;
lilypond -f pdf -o test -l NONE test/$filename.ly;
open test/$filename.pdf;
