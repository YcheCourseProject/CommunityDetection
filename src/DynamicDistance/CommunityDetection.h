#pragma once
#ifndef COMMUNITY_DETECTION_H
#define COMMUNITY_DETECTION_H

#include "Graph.h"

class CommunityDetection
{
private:
    Graph m_cGraph;
    bool m_bIsWeighted;
    int m_iCurrentStep;
    double m_dThreshold;

    map<EdgeKey, double> m_dictVirtualEdgeTempResult;
    map<EdgeKey, double> m_dictVirtualEdgeConverge;
private:
    void SetupGraph(const string& strFileName);
    void InitializeGraph();
    void DynamicInteraction();

private:
    void SetUnion(set<int>* left, set<int>* right, set<int>* dest);
    void SetDifference(set<int>* left, set<int>* right, set<int>* dest);
    void SetIntersection(set<int>* left, set<int>* right, set<int>* dest);

    double ComputeWeightedJaccardDistance(int iBegin, int iEnd, EdgeValue* pEdgeValue);
    double ComputeUnweightedJaccardDistance(int iBegin, int iEnd, EdgeValue* pEdgeValue);
    double ComputeJaccardDistance(int iBegin, int iEnd, EdgeValue* pEdgeValue);

    double ComputeDI(int iBegin, int iEnd, EdgeValue* pEdgeValue);
    double ComputeCI(int iBegin, int iEnd, EdgeValue* pEdgeValue, bool& bConverge);
    double ComputeEI(int iBegin, int iEnd, EdgeValue* pEdgeValue, bool& bConverge);
    double ComputePartialEI(int iTarget, int iTargetNeighbour, set<int>& targetEN, bool& bConverge);
    double ComputeInfluence(int iTargetNeighbour, int iENVertex, int iTarget, bool& bConverge);

    void ComputeExclusiveNeighbour(int iBegin, int iEnd, EdgeValue* pEdgeValue);
    void ComputeCommonNeighbour(int iBegin, int iEnd, EdgeValue* pEdgeValue);
    double ComputeVirtualDistance(int iBegin, int iEnd, int iTarget, bool& bConverge);

public:
    CommunityDetection(bool bIsWeighted, double dThreshold);
    void Execute(const string& strFileName);
    void OutputCommunities(string& strFileName);
    void OutputEdges(string& strFileName);
    static long iVirtualEdgeNumber;
    static long long iVirtualComputationNumber;
    static long iCommonEdgeNumber;
    static long long iCommonComputationNumber;
};
#endif
