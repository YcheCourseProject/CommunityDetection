#!/bin/bash
function recursiveRunMCL(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             recursiveRunMCL $1"/"$file
        else
            #echo $file
            if [[ $file =~ .*[0-9]+.csv ]]
            then
                myfile=$1"/"$file
                echo "run mcl ... input:"$file
                if [[ $file =~ .*road.* ]]
                then
                    ` mcl $myfile --abc -I 1.4 -o ${myfile//.csv/_output_mcl.csv} `   
                else
                    echo "Now road:"
                    ` mcl $myfile --abc -I 2 -o ${myfile//.csv/_output_mcl.csv} `                     
                fi
            fi
        fi
    done
}
INIT_PATH="/home/cheyulin/ClionProjects/Community-Detection/dataset/"
recursiveRunMCL $INIT_PATH

