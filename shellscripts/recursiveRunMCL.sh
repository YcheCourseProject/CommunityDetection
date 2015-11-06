        #!/bin/bash
function runMcl(){
    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]
        then
             runMcl $1"/"$file
        else
            echo $file
            if [[ $file =~ .*input.csv$ ]];then
                #run Mcl
                init_infile=$1"/"$file
                temp_clu_file=${init_infile//input.csv/output_mcl.csv}
                if [[ $file =~ .*road.* ]];then
                    echo "run road with inflation 1.4"
                    mcl $init_infile --abc -I 1.4 -o $temp_clu_file   
                else
                    mcl $init_infile --abc -I 2 -o $temp_clu_file                     
                fi

                #output processing
                java_path="/home/cheyulin/Community-Detection/java_project/bin"
                java_infomap_op_class="op.MclOP"
                cd $java_path
                clu_out_file=${init_infile//edges_input.csv/mcl.clu}
                java  $java_infomap_op_class $temp_clu_file $clu_out_file
                                
                #measurement
                truthfile=${file//edges_input.csv/ground_truth.csv}
                truth_file_num=$(find $1 -name $truthfile | wc -l)
                echo $truth_file_num
                if [[ $truth_file_num == "1" ]];then
                    if [[ $truthfile =~ .*amazon.* ]];then
                        echo "amazon"
                        #measurement_out_file=${init_infile//edges_input.clu/measurement_mcl.us}
                        #attractor -E US $clu_out_file $init_infile $measurement_out_file
                    else
                        ground_truth_file=$1"/"$truthfile
                        measurement_out_file=${init_infile//edges_input.csv/measurement_mcl.s}
                        attractor -E S  $clu_out_file $ground_truth_file $measurement_out_file
                    fi
                else
                    echo "hello"
                    measurement_out_file=${init_infile//edges_input.csv/measurement_mcl.us}
                    echo $clu_out_file" "$init_infile" "$measurement_out_file
                    attractor -E US $clu_out_file $init_infile $measurement_out_file
                fi
            fi
        fi
    done
}

INIT_PATH="/home/cheyulin/Community-Detection/dataset/synthetic"
runMcl $INIT_PATH

