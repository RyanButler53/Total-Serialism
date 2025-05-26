# Driving script for creating the scores and processing options. 

# ./score.sh <out_filename> <in_filename> [-p]
# ./score.sh seed [-p]
numArgs=$#; 

# Put all the scores in here!
mkdir -p scores

if  [ $numArgs == 0 ];
then 
    build/TotalSerialism;
    lilypond -f pdf random_score.ly; # -l NONE
    finalFile=random_score.pdf
    mv $finalFile scores
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
            mv score-$out_filename/ scores
            # rm params.txt 2> /dev/null
        elif [ $numArgs == 1 ];
        then
            seed=$1
            build/TotalSerialism -s $seed -p;
            cd score-random_score_seed_$seed;
            lilypond -f pdf -l NONE *.ly
            cd ..
            mv score-random_score_seed_$seed/ scores
            finalFile=score-random_score_seed_$seed/random_score_seed_$seed.pdf;
        else #No Arguments
            build/TotalSerialism;
            lilypond -f pdf -l NONE random_score.ly; 
            mv random_score.pdf scores
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
            # rm params.txt 2> /dev/null
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
        mv $finalFile scores
    fi
fi

# open $finalFile
