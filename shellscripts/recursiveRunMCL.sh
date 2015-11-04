#!/bin/bash
function recursiveRunMCL(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             recursiveRunMCL $1"/"$file
        else
            if [[ $file =~ .*input.csv$ ]]
            then
                myfile=$1"/"$file
                echo "run mcl ... input:"$file
                if [[ $file =~ .*road.* ]]
                then
                    echo "run road with inflation 1.4"
                    ` mcl $myfile --abc -I 1.4 -o ${myfile//input.csv/output_mcl.csv} `   
                else
                    ` mcl $myfile --abc -I 2 -o ${myfile//input.csv/output_mcl.csv} `                     
                fi
                JAVA_CLASS_PATH="/home/cheyulin/ClionProjects/Community-Detection/java_project/bin"
                CLASS_NAME="io.output.MCLOutputProcessor"
                cd ${JAVA_CLASS_PATH} 
                pwd 
                ` java  ${CLASS_NAME} ${myfile//input.csv/output_mcl.csv} ${myfile//input.csv/output_formalized_mcl.csv}`
            fi
        fi
    done
}
INIT_PATH="/home/cheyulin/ClionProjects/Community-Detection/dataset/synthetic"
recursiveRunMCL $INIT_PATH

