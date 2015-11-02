#include "CommunityDetection.h"
#include "ClusteringEvaluation.h"

double TestModularity(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictAdjacentList)
{
    double dModularity = 0;
    int iEdgeNumbers = 78;

    for (map<int, set<int>*>::iterator iterBegin = dictAdjacentList->begin(); iterBegin != dictAdjacentList->end(); iterBegin++)
    {
        int iSrc = iterBegin->first;
        for (map<int, set<int>*>::iterator iterEnd = dictAdjacentList->begin(); iterEnd != dictAdjacentList->end(); iterEnd++)
        {
            int iDest = iterEnd->first;
            int iSameCommunity = -1;
            int iLinkedEdgeNumber = iterBegin->second->count(iDest);
            int iSrcVertexDegree = iterBegin->second->size();
            int iDestVertexDegree = iterEnd->second->size();

            if (iDest == iSrc)
                continue;

            if (((*dictTargetCommunities)[1]->count(iSrc) != 0) && ((*dictTargetCommunities)[1]->count(iDest) != 0)
                || ((*dictTargetCommunities)[2]->count(iSrc) != 0) && ((*dictTargetCommunities)[2]->count(iDest) != 0))
            {
                iSameCommunity = 1;
            }

            dModularity += (iLinkedEdgeNumber - iSrcVertexDegree * iDestVertexDegree / (double)(2 * iEdgeNumbers)) * iSameCommunity;
        }
    }

    return  dModularity / (4 * iEdgeNumbers);
}

int main()
{
    string strInputFileName = "C:\\Users\\ssunah\\gitchina\\Community-Detection\\dataset\\small\\test\\test_edges_input.csv";
    string strOutputEdgeFileName = "output.csv";
    string strOutputCommunitiesFileName = "football_communities_output.csv";
    bool bIsWeighted = false;
    double dThreshold = 0.5;

    CommunityDetection communityDetection(bIsWeighted, dThreshold);

    communityDetection.Execute(strInputFileName);
    communityDetection.OutputEdges(strOutputEdgeFileName);
    communityDetection.OutputCommunities(strOutputCommunitiesFileName);

/*
    string strInputFileNameResult = "C:\\Users\\ssunah\\testdata\\ncut_result.csv";
    string strInputFileNameEdges = "C:\\Users\\ssunah\\testdata\\ncut_edges.csv";

    map<int, set<int>*>* pResultCommunities = ClusteringEvaluation::GenerateCommunities(strInputFileNameResult);
    map<int, set<int>*>* pAdjacentList = ClusteringEvaluation::GenerateAdjecentList(strInputFileNameEdges);

    double dNcut = ClusteringEvaluation::Ncuts(pResultCommunities, pAdjacentList);
    for (map<int, set<int>*>::iterator iter = pResultCommunities->begin(); iter != pResultCommunities->end(); iter++)
    {
        delete iter->second;
    }
    delete pResultCommunities;
    */
    return 0;
}