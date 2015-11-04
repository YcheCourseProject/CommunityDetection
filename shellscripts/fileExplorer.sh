#!/bin/bash
function ergodic(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             ergodic $1"/"$file
        else
            #echo $file
            if [[ $file =~ .*input.*csv$ ]] 
            then
                echo $file
            fi
        fi
    done
}
INIT_PATH="/home/cheyulin/ClionProjects/Community-Detection/dataset"
ergodic $INIT_PATH