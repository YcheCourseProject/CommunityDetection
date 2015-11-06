#!/bin/bash
function runMetis(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             runMetis $1"/"$file
        else
            if [[ $file =~ .*input.csv$ ]];then
                #input processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_metis_ip_class="ip.MetisIP"
                cd $java_path
                init_infile=$1"/"$file
                map_outfile=${init_infile//edges_input.csv/node_name_index1_map_metis.temp}
                neighbors_outfile=${init_infile//edges_input.csv/neighbors_index1_input_metis.temp}
                java $java_metis_ip_class $init_infile $map_outfile $neighbors_outfile

                partition_num="4"
                #run metis
                startTime=$(date +%s.%Nns)
                gpmetis $neighbors_outfile $partition_num
                endTime=$(date +%s.%Nns)
                temp_part_file=$neighbors_outfile".part."$partition_num
                temp_clu_file=${temp_part_file//neighbors_index1_input_/clu_} 
                mv $temp_part_file $temp_clu_file 
                echo $temp_clu_file

                #output processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_metis_op_class="op.MetisOP"
                cd $java_path
                clu_out_file=${init_infile//edges_input.csv/metis.clu}
                java  $java_metis_op_class $map_outfile $clu_out_file $temp_clu_file
            
                #measurement
                truthfile=${file//edges_input.csv/ground_truth.csv}
                truth_file_num=$(find $1 -name $truthfile | wc -l)
                echo $truth_file_num
                if [[ $truth_file_num == "1" ]];then
                    if [[ $truthfile =~ .*amazon.* ]];then
                        echo "amazon"
                        measurement_out_file=${init_infile//edges_input.clu/measurement_metis.us}
                        attractor -E US $clu_out_file $init_infile $measurement_out_file
                    else
                        ground_truth_file=$1"/"$truthfile
                        measurement_out_file=${init_infile//edges_input.csv/measurement_metis.s}
                        attractor -E S  $clu_out_file $ground_truth_file $measurement_out_file
                    fi
                else
                    echo "hello"
                    measurement_out_file=${init_infile//edges_input.csv/measurement_metis.us}
                    echo $clu_out_file" "$init_infile" "$measurement_out_file
                    attractor -E US $clu_out_file $init_infile $measurement_out_file
                fi
                
                echo "startTime:"$startTime >> $measurement_out_file
                echo "endTime:"$endTime >> $measurement_out_file

            fi

        fi
    done
}
INIT_PATH="/home/cheyulin/Community-Detection/dataset/big/collaboration"
runMetis $INIT_PATH

