#!/bin/bash
function removeTmpFiles(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             removeTmpFiles $1"/"$file
        else
            #echo $file
            if [[ $file =~ .*temp.* ]]
            then
                myfile=$1"/"$file
                echo $myfile
                    ` rm $myfile `                     
            fi
        fi
    done
}

