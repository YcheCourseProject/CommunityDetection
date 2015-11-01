#include "CommunityDetection.h"

void CommunityDetection::SetupGraph(const string &strFileName) {
    ifstream in(strFileName.c_str(), ios::in);
    int iBegin;
    int iEnd;
    double dWeight = 0;

    cout << "Setup Graph Start" << endl;
    const clock_t begin_time = clock();

    if (in.fail()) {
        cout << "Fail." << endl;
        exit(0);
    }

    int i = 0;

    while (!in.eof()) {
        in >> iBegin >> iEnd;

        if (m_bIsWeighted) {
            in >> dWeight;
        }
        EdgeValue *pNewEdgeValue = NULL;
        m_cGraph.AddActualEdge(iBegin, iEnd, dWeight, pNewEdgeValue);

        if (++i % 3000 == 0) {
            cout << "Line Number: " << i << endl;
        }
    }

    cout << "Setup Graph Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    in.close();
    in.clear();
}

void CommunityDetection::InitializeGraph() {
    map<EdgeKey, EdgeValue *> *pEdges = m_cGraph.GetEdges();
    double dDistance = 0;

    cout << "Initialize Graph Start" << endl;
    const clock_t begin_time = clock();

    int i = 0;

    for (map<EdgeKey, EdgeValue *>::iterator iter = pEdges->begin(); iter != pEdges->end(); iter++) {
        EdgeValue *pEdgeValue = iter->second;

        ComputeCommonNeighbour(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
        ComputeExclusiveNeighbour(iter->first.iBegin, iter->first.iEnd, pEdgeValue);

        dDistance = ComputeJaccardDistance(iter->first.iBegin, iter->first.iEnd, pEdgeValue);

        m_cGraph.UpdateActualEdge(iter->first.iBegin, iter->first.iEnd, dDistance, m_iCurrentStep);

        UpdateENDistance(iter->first.iBegin, *(pEdgeValue->pExclusiveNeighbours[END_POINT]));
        UpdateENDistance(iter->first.iEnd, *(pEdgeValue->pExclusiveNeighbours[BEGIN_POINT]));

        if (++i % 3000 == 0) {
            cout << "Line Number: " << i << endl;
        }
    }

    cout << "Initialize Graph Complete: " <<
    float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

}

void CommunityDetection::DynamicInteraction() {
    bool bContinue = true;

    map<EdgeKey, EdgeValue *> *pEdges = m_cGraph.GetEdges();

    cout << "Dynamic Iteraction Start" << endl;
    const clock_t begin_time = clock();

    int i = 0;
    while (bContinue) {
        bContinue = false;
        int iNextStep = Helper::NextStep(m_iCurrentStep);

        int iConvergeNumber = 0;

        for (map<EdgeKey, EdgeValue *>::iterator iter = pEdges->begin(); iter != pEdges->end(); iter++) {
            EdgeValue *pEdgeValue = iter->second;

            if (pEdgeValue->aDistance[m_iCurrentStep] > 0 && pEdgeValue->aDistance[m_iCurrentStep] < 1) {
                double dDI = ComputeDI(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
                double dCI = ComputeCI(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
                double dEI = ComputeEI(iter->first.iBegin, iter->first.iEnd, pEdgeValue);

                double delta = dDI + dCI + dEI;

                if (delta > PRECISE || delta < -PRECISE) {
                    double newDistance =
                            m_cGraph.ActualDistance(iter->first.iBegin, iter->first.iEnd, m_iCurrentStep) + delta;

                    m_cGraph.UpdateActualEdge(iter->first.iBegin, iter->first.iEnd, newDistance, iNextStep);

                    bContinue = true;
                }
            }
            else {
                pEdgeValue->aDistance[iNextStep] = pEdgeValue->aDistance[m_iCurrentStep];
                iConvergeNumber++;
            }
        }

        if (i % 2 == 0)
            cout << "Iteration: " << i << ", The Number of Converge Edges: " << iConvergeNumber
            << ", The Number of Left Edges: " << m_cGraph.GetEdges()->size() - iConvergeNumber << endl;

        ++i;

        Helper::UpdateStep(m_iCurrentStep);
    }

    cout << "Dynamic Iteraction Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
}

void CommunityDetection::OutputCommunities() {

}

void CommunityDetection::SetUnion(set<int> *left, set<int> *right, set<int> *dest) {
    set_union(left->begin(), left->end(),
              right->begin(), right->end(),
              inserter(*dest, dest->end()));
}

void CommunityDetection::SetDifference(set<int> *left, set<int> *right, set<int> *dest) {
    set_difference(left->begin(), left->end(),
                   right->begin(), right->end(),
                   inserter(*dest, dest->end()));
}

void CommunityDetection::SetIntersection(set<int> *left, set<int> *right, set<int> *dest) {
    set_intersection(left->begin(), left->end(),
                     right->begin(), right->end(),
                     inserter(*dest, dest->end()));
}

double CommunityDetection::ComputeWeightedJaccardDistance(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    set<int> allNeighbours;

    SetUnion(m_cGraph.GetVertexNeighbours(iBegin), m_cGraph.GetVertexNeighbours(iEnd), &allNeighbours);

    double sharedNeighboursWeight = 0;

    for (set<int>::iterator iter = pEdgeValue->pCommonNeighbours->begin();
         iter != pEdgeValue->pCommonNeighbours->end(); iter++) {
        if (*iter == iBegin || *iter == iEnd) {
            continue;
        }
        sharedNeighboursWeight += m_cGraph.Weight(iBegin, *iter) + m_cGraph.Weight(iEnd, *iter);
    }

    double allNeighboursWeight = 0;

    for (set<int>::iterator iterBegin = allNeighbours.begin(); iterBegin != allNeighbours.end(); iterBegin++) {
        set<int>::iterator iterEnd = iterBegin;
        iterEnd++;

        while (iterEnd != allNeighbours.end()) {
            allNeighboursWeight += m_cGraph.Weight(*iterBegin, *iterEnd);
        }
    }

    return 1 - sharedNeighboursWeight / allNeighboursWeight;
}

double CommunityDetection::ComputeUnweightedJaccardDistance(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    set<int> allNeighbours;

    SetUnion(m_cGraph.GetVertexNeighbours(iBegin), m_cGraph.GetVertexNeighbours(iEnd), &allNeighbours);

    return 1 - (double) pEdgeValue->pCommonNeighbours->size() / (double) allNeighbours.size();
}

double CommunityDetection::ComputeJaccardDistance(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    return m_bIsWeighted ? ComputeWeightedJaccardDistance(iBegin, iEnd, pEdgeValue)
                         : ComputeUnweightedJaccardDistance(iBegin, iEnd, pEdgeValue);
}

double CommunityDetection::ComputeDI(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    return -sin(1 - pEdgeValue->aDistance[m_iCurrentStep])
           * (1 / (double) (m_cGraph.GetVertexNeighbours(iBegin)->size() - 1)
              + 1 / (double) (m_cGraph.GetVertexNeighbours(iEnd)->size() - 1));
}

double CommunityDetection::ComputeCI(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    double dCI = 0;

    for (set<int>::iterator iter = pEdgeValue->pCommonNeighbours->begin();
         iter != pEdgeValue->pCommonNeighbours->end(); iter++) {
        int iSharedVertex = *iter;

        if (iBegin == iSharedVertex || iEnd == iSharedVertex) {
            continue;
        }

        dCI += sin(1 - m_cGraph.ActualDistance(iBegin, iSharedVertex, m_iCurrentStep)) *
               (1 - m_cGraph.ActualDistance(iEnd, iSharedVertex, m_iCurrentStep)) /
               (m_cGraph.GetVertexNeighbours(iBegin)->size() - 1)
               + sin(1 - m_cGraph.ActualDistance(iEnd, iSharedVertex, m_iCurrentStep)) *
                 (1 - m_cGraph.ActualDistance(iBegin, iSharedVertex, m_iCurrentStep)) /
                 (m_cGraph.GetVertexNeighbours(iEnd)->size() - 1);
    }

    return -dCI;
}

double CommunityDetection::ComputeEI(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    double dEI = 0;

    dEI += ComputePartialEI(iBegin, iEnd, *(pEdgeValue->pExclusiveNeighbours[BEGIN_POINT]))
           + ComputePartialEI(iEnd, iBegin, *(pEdgeValue->pExclusiveNeighbours[END_POINT]));

    return -dEI;
}

double CommunityDetection::ComputePartialEI(int iTarget, int iTargetNeighbour, set<int> &targetEN) {
    double dDistance = 0;

    for (set<int>::iterator iter = targetEN.begin(); iter != targetEN.end(); iter++) {
        dDistance += sin(1 - m_cGraph.ActualDistance(*iter, iTarget, m_iCurrentStep))
                     * ComputeInfluence(iTargetNeighbour, *iter)
                     / (m_cGraph.GetVertexNeighbours(iTarget)->size() - 1);
    }

    return dDistance;
}

double CommunityDetection::ComputeInfluence(int iTargetNeighbour, int iENVertex) {
    double dDistance = 1 - m_cGraph.VirtualDistance(iTargetNeighbour, iENVertex);

    if (dDistance >= m_dThreshold)
        return dDistance;

    return dDistance - m_dThreshold;
}

void CommunityDetection::ComputeExclusiveNeighbour(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    SetDifference(m_cGraph.GetVertexNeighbours(iBegin), pEdgeValue->pCommonNeighbours,
                  pEdgeValue->pExclusiveNeighbours[BEGIN_POINT]);
    SetDifference(m_cGraph.GetVertexNeighbours(iEnd), pEdgeValue->pCommonNeighbours,
                  pEdgeValue->pExclusiveNeighbours[END_POINT]);
}

void CommunityDetection::ComputeCommonNeighbour(int iBegin, int iEnd, EdgeValue *pEdgeValue) {
    SetIntersection(m_cGraph.GetVertexNeighbours(iBegin),
                    m_cGraph.GetVertexNeighbours(iEnd), pEdgeValue->pCommonNeighbours);
}

void CommunityDetection::ComputeVirtualDistance(int iBegin, int iEnd) {
    EdgeValue *pEdgeValue = NULL;
    if (m_cGraph.AddVirtualEdge(iBegin, iEnd, 0, pEdgeValue)) {
        ComputeCommonNeighbour(iBegin, iEnd, pEdgeValue);
        double dDistance = ComputeJaccardDistance(iBegin, iEnd, pEdgeValue);
        m_cGraph.UpdateVirtualEdge(iBegin, iEnd, dDistance, m_iCurrentStep);
    }
}

void CommunityDetection::UpdateENDistance(int iTarget, set<int> &setEN) {
    for (set<int>::iterator iter = setEN.begin(); iter != setEN.end(); iter++) {
        ComputeVirtualDistance(iTarget, *iter);
    }
}

CommunityDetection::CommunityDetection(bool bIsWeighted, double dThreshold) {
    m_bIsWeighted = bIsWeighted;
    m_dThreshold = dThreshold;
    m_iCurrentStep = 0;
}

void CommunityDetection::Execute(const string &strFileName) {
    SetupGraph(strFileName);
    InitializeGraph();
    DynamicInteraction();
}

void CommunityDetection::OutputCommunities(string &strFileName) {
    map<int, set<int> *> *pCommunities = m_cGraph.FindAllConnectedComponents();

    ofstream out(strFileName.c_str(), ios::out);

    cout << "Output Communities Start" << endl;
    const clock_t begin_time = clock();

    for (map<int, set<int> *>::iterator iter = pCommunities->begin(); iter != pCommunities->end(); iter++) {
        if (iter->second->size() <= 1)
            continue;

        for (set<int>::iterator iterVertex = iter->second->begin(); iterVertex != iter->second->end(); iterVertex++) {
            out << iter->first << ' ' << *iterVertex << endl;
        }
    }

    cout << "Output Communities Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    out.close();
    out.clear();
}

void CommunityDetection::OutputEdges(string &strFileName) {
    map<EdgeKey, EdgeValue *> *pEdges = m_cGraph.GetEdges();
    ofstream out(strFileName.c_str(), ios::out);

    cout << "Output edges Start" << endl;
    const clock_t begin_time = clock();

    for (map<EdgeKey, EdgeValue *>::iterator iter = pEdges->begin(); iter != pEdges->end(); iter++) {
        if (iter->second->aDistance[0] < 1)
            out << iter->first.iBegin << " " << iter->first.iEnd << endl;
    }

    cout << "Output edges Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    out.close();
    out.clear();
}

