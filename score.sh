# Driving script for creating the scores and processing options. 

numArgs=$#; 

if  [ $numArgs == 0 ];
then 
    build/TotalSerialism;
    lilypond -f pdf random_score.ly; # -l NONE
    finalFile=random_score.pdf
else
    # Check Parts
    if [ "${@: -1}" == "-p" ];
    then
        ((numArgs--))
        if [ $numArgs == 2 ]; 
        then # specify input and output
            out_filename=$1;
            in_filename=$2;
            build/TotalSerialism -o $out_filename.ly -i $in_filename -p;
            cd score-$out_filename
            lilypond -f pdf -l NONE *.ly
            cd ..
            finalFile=score-$out_filename/$out_filename.pdf
            rm params.txt 2> /dev/null
        elif [ $numArgs == 1 ];
        then
            seed=$1
            build/TotalSerialism -s $seed -p;
            cd score-random_score_seed_$seed;
            lilypond -f pdf -l NONE *.ly
            cd ..
            finalFile=score-random_score_seed_$seed/random_score_seed_$seed.pdf;
        else #No Arguments
            build/TotalSerialism;
            lilypond -f pdf -l NONE random_score.ly; 
            finalFile=random_score.pdf
        fi
    else # Not exporting Parts
        if [ $numArgs == 2 ]; 
        then # specify input and output
            out_filename=$1;
            in_filename=$2;
            build/TotalSerialism -o $out_filename.ly -i $in_filename;
            lilypond -f pdf -l NONE $out_filename.ly;
            finalFile=$(basename $out_filename).pdf
            rm params.txt 2> /dev/null
        elif [ $numArgs == 1 ];
        then
            seed=$1
            build/TotalSerialism -s $seed;
            lilypond -f pdf -l NONE random_score_seed_$seed.ly;
            finalFile=random_score_seed_$seed.pdf;
        else #No Other Arguments is not supported
            build/TotalSerialism;
            lilypond -f pdf -l NONE random_score.ly; 
            finalFile=random_score.pdf
        fi
    fi
fi

open $finalFile
