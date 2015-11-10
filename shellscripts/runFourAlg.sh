source /home/cheyulin/Community-Detection/shellscripts/removeTempFiles.sh
source /home/cheyulin/Community-Detection/shellscripts/recursiveRunAttractorRemoveTail.sh
INIT_PATH="/home/cheyulin/Community-Detection/dataset/big/road"

echo "start run Attractor_Improve_Both"
runAttractorRmTailor $INIT_PATH

echo "start run Attractor_Old"
runAttractor $INIT_PATH

echo "remove Tmp Files"
removeTmpFiles $INIT_PATH
