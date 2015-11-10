source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractor.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractorImproveEIComp.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractorRemoveTail.sh
INIT_PATH="/home/cheyulin/Community-Detection/dataset/big/road"

echo "start run Attractor_Newest"
runAttractorRmTailor $INIT_PATH 10

echo "start run Attractor_Vertext_Influence"
runAttractorImproveEIOnly $INIT_PATH 10

echo "start run Attractor"
runAttractor $INIT_PATH

echo "remove Tmp Files"
removeTmpFiles $INIT_PATH
