#!/bin/bash
n=${1:-10}
echo "Running $n Random tests"
rm -rf fuzz;
mkdir fuzz;
for seed in $(seq 1 $n); do
    build/totalSerialism $seed;
    mv random_score_seed_$seed.ly fuzz
    cd fuzz
    lilypond -f pdf -l WARN random_score_seed_$seed.ly 2>err$seed.txt
    cd ..
done;
build/fuzzEval $n
cd fuzz
rm *.pdf
rm *.ly