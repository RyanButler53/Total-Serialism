numArgs=$#; 
if [ $numArgs == 2 ]; 
then # specify input and output
    out_filename=$1;
    in_filename=$2;
    build/totalSerialism $out_filename.ly $in_filename;
    lilypond -f pdf  $out_filename.ly; # -o folder -l NONE
    finalFile=$(basename $out_filename).pdf
    # rm params.txt 2> /dev/null
elif [ $numArgs == 1 ];
then
    seed=$1
    build/totalSerialism  $seed;
    lilypond -f pdf random_score_seed_$seed.ly; # -o folder -l NONE 
    finalFile=random_score_seed_$seed.pdf;
else #No Arguments
    build/totalSerialism;
    lilypond -f pdf random_score.ly; # -l NONE
    finalFile=random_score.pdf
fi
open $finalFile
