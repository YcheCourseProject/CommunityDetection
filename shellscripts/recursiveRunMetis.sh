#!/bin/bash
function runMetis(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             runMetis $1"/"$file
        else
            #input processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_louvain_ip_class="ip.LouvainIP"
                cd $java_path
                init_infile=$1"/"$file
                map_outfile=${init_infile//edges_input.csv/node_name_index1_map_metis.temp}
                edge_outfile=${init_infile//input.csv/index1_input_metis.temp}
                java $java_louvain_ip_class $init_infile $map_outfile $edge_outfile

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
runMetis $INIT_PATH

