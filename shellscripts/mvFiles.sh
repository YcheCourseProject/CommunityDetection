#!/bin/bash
function mvFiles(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             mvFiles $1"/"$file
        else
            #echo $file
            if [[ $file =~ .*input_edges.csv* ]]
            then
                cd $1
                newfile=${file//input_edges/edges_input} 
                mv $file $newfile            
            fi
        fi
    done
}

INIT_PATH="/home/cheyulin/Community-Detection/dataset/synthetic/test_case_5"
mvFiles $INIT_PATH

