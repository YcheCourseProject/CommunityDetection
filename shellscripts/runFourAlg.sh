source /home/cheyulin/Community-Detection/shellscripts/recursiveRunLouvain.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunInfomap.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunMCL.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractor.sh
source /home/cheyulin/Community-Detection/shellscripts/removeTempFiles.sh
INIT_PATH="/home/cheyulin/Community-Detection/dataset/big"

echo "start run Louvain"
runLouvain $INIT_PATH

echo "start run Infomap"
runInfomap $INIT_PATH

echo "start run MCL"
runMcl $INIT_PATH

echo "start run Attractor"
runAttractor $INIT_PATH

echo "remove Tmp Files"
removeTmpFiles $INIT_PATH
