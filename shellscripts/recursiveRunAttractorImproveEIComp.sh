#!/bin/bash
function runAttractorImproveEIOnly(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ];then
             runAttractorImproveEIOnly $1"/"$file $2
        else
            if [[ $file =~ .*input.csv$ ]];then
                init_infile=$1"/"$file
                declare -i lamda=4
                while((lamda < 8))
                do
                    #run attractor
                    lamda_str=0"."$lamda
                    if((lamda == 10));then
                        lamda_str="1.0";
                    fi
                    output_attractor_improveEIonly_suffix="_attractor_improveEIonly_"$2_$lamda_str".clu"
                    output_connected_componets_attractor_improveEIonly_suffix="_attractor_improveEIonly_"$2_$lamda_str".cc"
                    clu_out_file=${init_infile//edges_input.csv/${output_attractor_improveEIonly_suffix}};
                    components_outfile=${init_infile//edges_input.csv/${output_connected_componets_attractor_improveEIonly_suffix}} 

                    startTime=$(date +%s.%Nns)
                    window_size="10"
                    attractorImproveEI -A $lamda_str 0 $init_infile $clu_out_file $components_outfile  $2       
                    endTime=$(date +%s.%Nns)
                    echo "hello"
                    echo $clu_out_file

                    #measurement
                    truthfile=${file//edges_input.csv/ground_truth.csv}
                    echo $truthfile
                    truth_file_num=$(find $1 -name $truthfile | wc -l)
                    echo $truth_file_num
                    if [[ $truth_file_num == "1" ]];then
                        if [[ $truthfile =~ .*amazon.* ]];then
                            echo "amazon"
                            measurement_out_file=${init_infile//edges_input.csv/measurement_attractor_improveEIonly_$2_$lamda_str.us}
                            attractorImproveEI -E US $clu_out_file $init_infile $measurement_out_file
                        else
                            echo "s"
                            ground_truth_file=$1"/"$truthfile
                            measurement_out_file=${init_infile//edges_input.csv/measurement_attractor_improveEIonly_$2_$lamda_str.s}
                            attractorImproveEI -E S  $clu_out_file $ground_truth_file $measurement_out_file 
                        fi
                    else
                        echo "us"
                        measurement_out_file=${init_infile//edges_input.csv/measurement_attractor_improveEIonly_$2_$lamda_str.us}
                        echo $clu_out_file" "$init_infile" "$measurement_out_file
                        attractorImproveEI -E US $clu_out_file $init_infile $measurement_out_file
                    fi
                    echo "startTime:"$startTime >> $measurement_out_file
                    echo "endTime:"$endTime >> $measurement_out_file
                    let lamda+=1
                done
            fi
        fi
    done


}




