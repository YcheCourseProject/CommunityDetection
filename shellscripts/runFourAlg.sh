source /home/cheyulin/Community-Detection/shellscripts/recursiveRunLouvain.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunInfomap.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunMCL.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractor.sh
source /home/cheyulin/Community-Detection/shellscripts/removeTempFiles.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractorRemoveTail.sh
INIT_PATH="/home/cheyulin/Community-Detection/dataset/synthetic/test_case_5"

echo "start run Attractor_Newest"
runAttractorRmTailor $INIT_PATH

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
