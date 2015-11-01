#include "CommunityDetection.h"

int main() {
    string strInputFileName = "C:\\Users\\ssunah\\gitchina\\Community-Detection\\dataset\\big\\collaboration\\collaboration_edges_input.csv";
    string strOutputEdgeFileName = "collaboration_edges_output.csv";
    string strOutputCommunitiesFileName = "collaboration_communities_output.csv";
    bool bIsWeighted = false;
    double dThreshold = 0.5;

    CommunityDetection communityDetection(bIsWeighted, dThreshold);

    communityDetection.Execute(strInputFileName);
    communityDetection.OutputEdges(strOutputEdgeFileName);
    communityDetection.OutputCommunities(strOutputCommunitiesFileName);

    return 0;
}