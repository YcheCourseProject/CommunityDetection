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
#include <string>
#include "Helper.h"
#include "string.h"

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

    map<EdgeKey, EdgeValue*> m_dictEdges;
    map<int, VertexValue*> m_dictVertices;

private:
    void AddVertex(int iBegin, int iEnd);
    void ClearVertices();
    void ClearEdges();

public:
    bool AddEdge(int iBegin, int iEnd, double dWeight, EdgeValue* &pNewEdgeValue);
    void UpdateEdge(int iBegin, int iEnd, double dNewDistance, int iStep);
    double Distance(int iBegin, int iEnd, int iStep);
    double Weight(int iBegin, int iEnd);

    map<int, set<int>* >* FindAllConnectedComponents();
    map<EdgeKey, EdgeValue*>* GetAllEdges();
    set<int>* GetVertexNeighbours(int iVertexId);

    ~Graph();

    static void RefineEdgeKey(int& iBegin, int& iEnd);
};

#endif