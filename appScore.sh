# Modified down version of the Total Serialism 
# score.sh script for the app speciic case

# Driving script for creating the scores and processing options. 

numArgs=$#; 

out_filename=$1
script_path=$2
output_path=$3
cd $script_path

if [ $numArgs == 4 ];
then  # outfilename, pathToScript,outfilePath, parts
    build/TotalSerialism -o $out_filename.ly -i params.txt -p;
    rm params.txt
    cd $output_path
    cd score-$out_filename
    lilypond -f pdf -l NONE *.ly
    cd ..
    finalFile=score-$out_filename/$out_filename.pdf
else # outfilename, path
    build/TotalSerialism -o $out_filename.ly -i params.txt;
    rm params.txt
    cd $output_path
    lilypond -f pdf -l NONE $out_filename.ly;
    finalFile=$(basename $out_filename).pdf
fi
open $finalFile