#!/bin/bash
function removeFiles(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             removeFiles $1"/"$file
        else
            #echo $file
            if [[ $file =~ .*infomap.*$ || $file =~ .*metis.*$ || $file =~ .*mcl.*$ || $file =~ .*pname.*$ || $file =~ .*map.*$ || $file =~ .*clu$ || $file =~ .*map$ || $file =~ .*tree$ ]]
            then
                myfile=$1"/"$file
                echo $myfile
                    ` rm $myfile `                     
            fi
        fi
    done
}
INIT_PATH="/home/cheyulin/ClionProjects/Community-Detection/dataset/"
removeFiles $INIT_PATH

