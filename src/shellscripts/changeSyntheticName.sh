#!/bin/bash
function ergodic(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             ergodic $1"/"$file
        else
            #echo $file
            if [[ $file =~ .*[0-9]+.csv ]]
            then
                myfile=$1"/"$file
	            echo "old:"${myfile}
                mv $myfile ${myfile//.csv/_edges_input.csv} 
            fi
        fi
    done
}
INIT_PATH="/home/cheyulin/Community-Detection/dataset/synthetic"
ergodic $INIT_PATH

