#pragma once

#ifndef COMMUNITY_DETECTION_GRAPH_H
#define COMMUNITY_DETECTION_GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <ctime>
#include <queue>
#include <math.h>
#include "Helper.h"

using namespace std;

#define STEP_LENGTH 2
#define EDGE_ENDPOINT_NUMBER 2
#define BEGIN_POINT 0
#define END_POINT 1
#define PRECISE 0.0000001

struct EdgeKey {
    int iBegin;
    int iEnd;

    bool operator<(const EdgeKey &right) const {
        if (iBegin == right.iBegin) {
            return iEnd < right.iEnd;
        }

        return iBegin < right.iBegin;
    }
};

struct EdgeValue {
    double dWeight;
    double aDistance[STEP_LENGTH];
    set<int> *pCommonNeighbours;
    set<int> *pExclusiveNeighbours[EDGE_ENDPOINT_NUMBER];
};

struct VertexValue {
    set<int> *pNeighbours;
};

class Graph {
private:
    map<EdgeKey, EdgeValue *> m_dictActualEdges;
    map<EdgeKey, EdgeValue *> m_dictVirtualEdges;
    map<int, VertexValue *> m_dictVertices;

private:
    void AddVertex(int iBegin, int iEnd);

    bool AddEdge(int iBegin, int iEnd, double dWeight, map<EdgeKey, EdgeValue *> &dictEdges, EdgeValue *&pNewEdgeValue,
                 bool bIsActual = true);

    void UpdateEdge(int iBegin, int iEnd, double dDistance, int iStep, map<EdgeKey, EdgeValue *> &dictEdges);

    void RefineEdgeKey(int &iBegin, int &iEnd);

    void ClearVertices();

    void ClearEdges(map<EdgeKey, EdgeValue *> &dictEdges);

public:
    bool AddActualEdge(int iBegin, int iEnd, double dWeight, EdgeValue *&pNewEdgeValue);

    bool AddVirtualEdge(int iBegin, int iEnd, double dWeight, EdgeValue *&pNewEdgeValue);

    void UpdateActualEdge(int iBegin, int iEnd, double dNewDistance, int iStep);

    void UpdateVirtualEdge(int iBegin, int iEnd, double dNewDistance, int iStep = 0);

    double ActualDistance(int iBegin, int iEnd, int iStep);

    double VirtualDistance(int iBegin, int iEnd);

    double Weight(int iBegin, int iEnd);

    map<int, set<int> *> *FindAllConnectedComponents();

    map<EdgeKey, EdgeValue *> *GetEdges();

    set<int> *GetVertexNeighbours(int iVertexId);

    ~Graph();
};

#endif