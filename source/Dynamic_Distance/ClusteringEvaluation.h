#pragma once
#ifndef CLUSTERING_EVALUATION_H
#define CLUSTERING_EVALUATION_H

#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class ClusteringEvaluation
{
public:
    static map<int, set<int>* >* GenerateCommunities(const string& strFileName);
    static map<int, set<int>* >* GenerateAdjecentList(const string& strFileName);
    static void ClearResources(map<int, set<int>* >* pTarget);

    static double SimplyPurity(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictGroundTruth);
    static double InversePurity(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictGroundTruth);
    static double Purity(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictGroundTruth);

    static double NMI(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictGroundTruth);
    static double ARI(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictGroundTruth);
    static double RI(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictGroundTruth);
    static double Modularity(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictAdjacentList);
    static double Ncut(map<int, set<int>* >* dictTargetCommunities, map<int, set<int>* >* dictAdjacentList);

    static double AverageDegree(map<int, set<int>* >* dictAdjacentList);
    static double LocalClusteringCoefficient(map<int, set<int>* >* dictAdjacentList);
    static int VerticesNumberFromCommunities(map<int, set<int>*>* pTarget);
    static int VerticesNumberFromAdjacentList(map<int, set<int>*>* dictAdjacentList);
    static int EdgesNumber(map<int, set<int>* >* dictAdjacentList);

    static double F_Measure(double dFirstValue, double dSecondValue);
private:
    static int CommonVertexNumber(set<int>* pSrc, set<int>* pDest);
    static int TwoCombinationSum(map<int, set<int>*>* pSrc);
    static int TwoCombinationSum(map<int, set<int>*>* pTarget, map<int, set<int>*>* pGroudTruth);
    static int TwoCombination(int iNumber);
    static int ComputeVolumeSum(set<int>* pSrcCommunity, map<int, set<int>* >* dictAdjacentList);
    static int ComputeCutSum(set<int>* pSrcCommunity, map<int, set<int>* >* dictAdjacentList);
};
#endif
