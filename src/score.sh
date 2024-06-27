numArgs=$#; 
if [ numArgs == 2 ]
then # specify input and output
    out_filename=$1;
    in_filename=$2;
    ./totalSerialism $out_filename.ly $input_filename
    lilypond -f pdf -l NONE $out_filename.ly; # -o folder
    finalFile=$out_filename.pdf
else # use randomness
    seed=${1:-70}
    ./totalSerialism  $seed;
    lilypond -f pdf -l NONE random_score_seed_$seed.ly; # -o folder
    finalFile=random_score_seed_$seed.pdf
fi
echo "Opening $finalFile"
open $finalFile
