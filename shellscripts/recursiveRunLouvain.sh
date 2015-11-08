#!/bin/bash
function runLouvain(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             runLouvain $1"/"$file
        else
            if [[ $file =~ .*input.csv$ ]];then
                #input processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_louvain_ip_class="ip.LouvainIP"
                cd $java_path
                init_infile=$1"/"$file
                map_outfile=${init_infile//edges_input.csv/node_name_index0_map_louvain.temp}
                edge_outfile=${init_infile//input.csv/index0_input_louvain.temp}
                echo $init_infile
                echo $map_outfile
                echo $edge_outfile
                java $java_louvain_ip_class $init_infile $map_outfile $edge_outfile
                
                #exec Louvain
                louvain_path="/home/cheyulin/Community-Detection-2/Louvain"
                cd $louvain_path
                convert_bin_file=${init_infile//edges_input.csv/temp_input_louvain.bin} 
                temp_tree_file=${init_infile//edges_input.csv/temp_input_louvain.tree}
                temp_clu_file=${init_infile//edges_input.csv/clu_louvain.temp}
                ./convert -i $edge_outfile -o $convert_bin_file
                startTime=$(date +%s.%Nns)
                ./community $convert_bin_file -l -1 > $temp_tree_file
                endTime=$(date +%s.%Nns)
                ./hierarchy  $temp_tree_file -l 1 > $temp_clu_file

                #output processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_louvain_op_class="op.LouvainOP"
                cd $java_path
                clu_out_file=${init_infile//edges_input.csv/louvain.clu}
                java $java_louvain_op_class $map_outfile $clu_out_file $temp_clu_file
           
                #measurement
                truthfile=${file//edges_input.csv/ground_truth.csv}
                truth_file_num=$(find $1 -name $truthfile | wc -l)
                echo $truth_file_num
                if [[ $truth_file_num == "1" ]];then
                    if [[ $truthfile =~ .*amazon.* ]];then
                        echo "amazon"
                        measurement_out_file=${init_infile//edges_input.csv/measurement_louvain.us}
                        echo $clu_out_file
                        echo $init_infile 
                        echo $measurement_out_file
                        attractor -E US $clu_out_file $init_infile $measurement_out_file
                    else
                        ground_truth_file=$1"/"$truthfile
                        measurement_out_file=${init_infile//edges_input.csv/measurement_louvain.s}
                        attractor -E S  $clu_out_file $ground_truth_file $measurement_out_file
                    fi
                else
                    echo "hello"
                    measurement_out_file=${init_infile//edges_input.csv/measurement_louvain.us}
                    echo $clu_out_file" "$init_infile" "$measurement_out_file
                    attractor -E US $clu_out_file $init_infile $measurement_out_file
                fi
                echo "startTime:"$startTime >> $measurement_out_file
                echo "endTime:"$endTime >> $measurement_out_file
            fi
        fi
    done
}


