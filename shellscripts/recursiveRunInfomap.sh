#!/bin/bash
function runInfomap(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             runInfomap $1"/"$file
        else
            if [[ $file =~ .*input.csv$ ]]
            then
                #input processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_infomap_ip_class="ip.InfomapIP"
                cd $java_path
                init_infile=$1"/"$file
                map_outfile=${init_infile//edges_input.csv/node_name_index1_map_infomap.temp}
                edge_outfile=${init_infile//input.csv/index1_input_infomap.temp}
                java $java_infomap_ip_class $init_infile $map_outfile $edge_outfile
                
                #run Infomap
                startTime=$(date +%s.%Nns)
                Infomap -i --link-list -N 10 --tree --map --clu  $edge_outfile $1
                endTime=$(date +%s.%Nns)
                temp_clu_file=${init_infile//edges_input.csv/clu_infomap.temp}
                temp_tree_file=${init_infile//edges_input.csv/tree_infomap.temp}
                temp_map_file=${init_infile//edges_input.csv/map_infomap.temp}
                mv  ${edge_outfile//.temp/.clu} $temp_clu_file
                mv  ${edge_outfile//.temp/.tree} $temp_tree_file
                mv  ${edge_outfile//.temp/.map} $temp_map_file
                
                #output processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_infomap_op_class="op.InfomapOP"
                cd $java_path
                clu_out_file=${init_infile//edges_input.csv/infomap.clu}
                java $java_infomap_op_class $map_outfile $clu_out_file $temp_tree_file

                #measurement
                truthfile=${file//edges_input.csv/ground_truth.csv}
                truth_file_num=$(find $1 -name $truthfile | wc -l)
                echo $truth_file_num
                if [[ $truth_file_num == "1" ]];then
                    if [[ $truthfile =~ .*amazon.* ]];then
                        echo "amazon"
                        measurement_out_file=${init_infile//edges_input.csv/measurement_infomap.us}
                        attractor -E US $clu_out_file $init_infile $measurement_out_file
                    else
                        ground_truth_file=$1"/"$truthfile
                        measurement_out_file=${init_infile//edges_input.csv/measurement_infomap.s}
                        attractor -E S  $clu_out_file $ground_truth_file $measurement_out_file
                    fi
                else
                    echo "hello"
                    measurement_out_file=${init_infile//edges_input.csv/measurement_infomap.us}
                    echo $clu_out_file" "$init_infile" "$measurement_out_file
                    attractor -E US $clu_out_file $init_infile $measurement_out_file
               
                fi

                echo "startTime:"$startTime >> $measurement_out_file
                echo "endTime:"$endTime >> $measurement_out_file
            fi
        fi
    done
}


