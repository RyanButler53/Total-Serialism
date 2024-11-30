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
    chmod 755 $output_path/score-$out_filename/compile
else # outfilename, path
    build/TotalSerialism -o $out_filename.ly -i params.txt;
    chmod 755 $output_path/compile
fi
