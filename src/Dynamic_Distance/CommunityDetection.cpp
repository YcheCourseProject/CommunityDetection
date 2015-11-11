#include "CommunityDetection.h"


long long CommunityDetection::iCommonComputationNumber = 0;
long CommunityDetection::iCommonEdgeNumber = 0;
long long CommunityDetection::iVirtualCommonComputationNumber = 0;
long long CommunityDetection::iVirtualEnNumber = 0;
long CommunityDetection::iVirtualEdgeNumber = 0;


void CommunityDetection::SetupGraph(const string & strFileName)
{
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
        m_cGraph.AddEdge(iBegin, iEnd, dWeight, pNewEdgeValue);


        if (++i % 100000 == 0)
        {
            cout << "Line Number: " << i << endl;
        }
    }

    cout << "Setup Graph Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    in.close();
    in.clear();
}


void CommunityDetection::InitializeGraph()
{
    map<EdgeKey, EdgeValue*>* pEdges = m_cGraph.GetAllEdges();
    double dDistance = 0;

    cout << "Initialize Graph Start" << endl;
    const clock_t begin_time = clock();

    int i = 0;

    for (map<EdgeKey, EdgeValue *>::iterator iter = pEdges->begin(); iter != pEdges->end(); iter++) {
        EdgeValue *pEdgeValue = iter->second;

        ComputeCommonNeighbour(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
        ComputeExclusiveNeighbour(iter->first.iBegin, iter->first.iEnd, pEdgeValue);

        dDistance = ComputeJaccardDistance(iter->first.iBegin, iter->first.iEnd, pEdgeValue);

        m_cGraph.UpdateEdge(iter->first.iBegin, iter->first.iEnd, dDistance, m_iCurrentStep);
        m_cGraph.AddVertexWeight(iter->first.iBegin, dDistance, m_iCurrentStep);
        m_cGraph.AddVertexWeight(iter->first.iEnd, dDistance, m_iCurrentStep);


        if (++i % 100000 == 0)
        {
            cout << "Line Number: " << i << endl;
        }
    }

    cout << "Initialize Graph Complete: " <<
    float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

}

void CommunityDetection::DynamicInteraction() {
    bool bContinue = true;


    map<EdgeKey, EdgeValue*>* pEdges = m_cGraph.GetAllEdges();

    cout << "Dynamic Iteraction Start" << endl;
    const clock_t begin_time = clock();

    int i = 0;
    while (bContinue) {
        bContinue = false;
        int iNextStep = Helper::NextStep(m_iCurrentStep);

        int iConvergeNumber = 0;


        int j = 0;
        long long ciTime = 0;
        long eiTime = 0;
        for (map<EdgeKey, EdgeValue*>::iterator iter = pEdges->begin(); iter != pEdges->end(); iter++)
        {
            EdgeValue* pEdgeValue = iter->second;

            if (pEdgeValue->aDistance[m_iCurrentStep] > 0 && pEdgeValue->aDistance[m_iCurrentStep] < 1)
            {

                double dDI = ComputeDI(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
                const clock_t cibegin_time = clock();
                double dCI = ComputeCI(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
                const clock_t eiBegin_time = clock();
                ciTime += eiBegin_time - cibegin_time;
                double dEI = ComputeEI(iter->first.iBegin, iter->first.iEnd, pEdgeValue);
                eiTime += clock() - eiBegin_time;
                double delta = dDI + dCI + dEI;



                if (delta > PRECISE || delta < -PRECISE)
                {
                    //add delta to delta window of edge
                    pEdgeValue->addNewDelta2Window(delta);
    
                    double newDistance = m_cGraph.Distance(iter->first.iBegin, iter->first.iEnd, m_iCurrentStep) + delta;

                    if (newDistance > 1 - PRECISE)
                    {
                        newDistance = 1;
                    }
                    else if (newDistance < PRECISE)
                    {
                        newDistance = 0;
                    }

                    m_cGraph.UpdateEdge(iter->first.iBegin, iter->first.iEnd, newDistance, iNextStep);
                    m_cGraph.AddVertexWeight(iter->first.iBegin, newDistance, iNextStep);
                    m_cGraph.AddVertexWeight(iter->first.iEnd, newDistance, iNextStep);
                    bContinue = true;
                }
            }

            else
            {
                double newDistance = pEdgeValue->aDistance[iNextStep] = pEdgeValue->aDistance[m_iCurrentStep];
                m_cGraph.AddVertexWeight(iter->first.iBegin, newDistance, iNextStep);
                m_cGraph.AddVertexWeight(iter->first.iEnd, newDistance, iNextStep);

                iConvergeNumber++;
            }

            if (++j % 100000 == 0)
            {
//                cout << "LineNumber: " << j << endl;
//                cout << "CI Time: " << ciTime << endl;
//                cout << "EI Time: " << eiTime << endl;
//                cout << "CI Computation: " << iCommonComputationNumber << endl;
//                cout << "EI Edge: " << iVirtualEdgeNumber << endl;
//                cout << "EI Common Computation: " << iVirtualCommonComputationNumber << endl;
//                cout << "EI EN Computation: " << iVirtualEnNumber << endl;
            }
        }


//        cout << "Iteration: " << ++i << ", The Number of Converge Edges: " << iConvergeNumber
//            << ", The Number of Left Edges: " << m_cGraph.GetAllEdges()->size() - iConvergeNumber << endl;
//        cout << "LineNumber: " << j << endl;
//        cout << "CI Time: " << ciTime << endl;
//        cout << "EI Time: " << eiTime << endl;
//        cout << "CI Computation: " << iCommonComputationNumber << endl;
//        cout << "EI Edge: " << iVirtualEdgeNumber << endl;
//        cout << "EI Computation: " << iVirtualCommonComputationNumber << endl;

        m_cGraph.ClearVertexWeight(m_iCurrentStep);
        m_dictVirtualEdgeTempResult.clear();
        m_dictInteration[i] = iConvergeNumber;
        Helper::UpdateStep(m_iCurrentStep);
    }

    cout << "Dynamic Iteraction Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

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


double CommunityDetection::ComputeWeightedJaccardDistance(int iBegin, int iEnd, EdgeValue * pEdgeValue)
{
    double sharedNeighboursWeight = 0;

    for (set<int>::iterator iter = pEdgeValue->pCommonNeighbours->begin(); iter != pEdgeValue->pCommonNeighbours->end(); iter++)
    {
        sharedNeighboursWeight += m_cGraph.Weight(iBegin, *iter) + m_cGraph.Weight(iEnd, *iter);
    }

    set<int>* pBeginNeighbours = m_cGraph.GetVertexNeighbours(iBegin);
    set<int>* pEndNeighbours = m_cGraph.GetVertexNeighbours(iEnd);
    double allNeighboursWeight = 0;


    for (set<int>::iterator iter = pBeginNeighbours->begin(); iter != pBeginNeighbours->end(); iter++)
    {
        allNeighboursWeight += m_cGraph.Weight(iBegin, *iter);
    }

    for (set<int>::iterator iter = pEndNeighbours->begin(); iter != pEndNeighbours->end(); iter++)
    {
        allNeighboursWeight += m_cGraph.Weight(iEnd, *iter);
    }

    return allNeighboursWeight == 0 ? 1 : 1 - sharedNeighboursWeight / allNeighboursWeight;
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

        * (1 / (double)(m_cGraph.GetVertexNeighbours(iBegin)->size() - 1)
            + 1 / (double)(m_cGraph.GetVertexNeighbours(iEnd)->size() - 1));
}


double CommunityDetection::ComputeCI(int iBegin, int iEnd, EdgeValue * pEdgeValue)
{

    double dCI = 0;

    for (set<int>::iterator iter = pEdgeValue->pCommonNeighbours->begin();
         iter != pEdgeValue->pCommonNeighbours->end(); iter++) {
        int iSharedVertex = *iter;

        if (iBegin == iSharedVertex || iEnd == iSharedVertex) {
            continue;
        }


        double dBegin = m_cGraph.Distance(iBegin, iSharedVertex, m_iCurrentStep);
        double dEnd = m_cGraph.Distance(iEnd, iSharedVertex, m_iCurrentStep);

        dCI += sin(1 - dBegin) * (1 - dEnd) / (m_cGraph.GetVertexNeighbours(iBegin)->size() - 1)
            + sin(1 - dEnd) * (1 - dBegin) / (m_cGraph.GetVertexNeighbours(iEnd)->size() - 1);


        iCommonComputationNumber++;
    }

    return -dCI;
}


double CommunityDetection::ComputeEI(int iBegin, int iEnd, EdgeValue * pEdgeValue)
{
    double dEI = 0;

    dEI += ComputePartialEI(iBegin, iEnd, *(pEdgeValue->pExclusiveNeighbours[BEGIN_POINT]))
        + ComputePartialEI(iEnd, iBegin, *(pEdgeValue->pExclusiveNeighbours[END_POINT]));


    return -dEI;
}


double CommunityDetection::ComputePartialEI(int iTarget, int iTargetNeighbour, set<int>& targetEN)
{

    double dDistance = 0;


    for (set<int>::iterator iter = targetEN.begin(); iter != targetEN.end(); iter++)
    {
        ++iVirtualEdgeNumber;
        dDistance += sin(1 - m_cGraph.Distance(*iter, iTarget, m_iCurrentStep))
            * ComputeInfluence(iTargetNeighbour, *iter, iTarget)
            / (m_cGraph.GetVertexNeighbours(iTarget)->size() - 1);
    }

    return dDistance;
}


double CommunityDetection::ComputeInfluence(int iTargetNeighbour, int iENVertex, int iTarget)
{
    double dDistance = 1 - ComputeVirtualDistance(iTargetNeighbour, iENVertex, iTarget);

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


double CommunityDetection::ComputeVirtualDistance(int iBegin, int iEnd, int iTarget)
{
    int iTempBegin = iBegin;
    int iTempEnd = iEnd;

    Graph::RefineEdgeKey(iTempBegin, iTempEnd);

    EdgeKey edgeKey{ iTempBegin, iTempEnd };

    if (m_dictVirtualEdgeTempResult.count(edgeKey) != 0)
    {
        return m_dictVirtualEdgeTempResult[edgeKey];
    }


    double dNumerator = 0;
    set<int>* pBeginNeighbours = m_cGraph.GetVertexNeighbours(iBegin);
    set<int>* pEndNeighbours = m_cGraph.GetVertexNeighbours(iEnd);

    set<int> setCommonNeighbours;

    SetIntersection(pBeginNeighbours, pEndNeighbours, &setCommonNeighbours);

    for (set<int>::iterator iter = setCommonNeighbours.begin(); iter != setCommonNeighbours.end(); iter++)
    {
        double dBegin = m_cGraph.Distance(iBegin, *iter, m_iCurrentStep);
        double dEnd = m_cGraph.Distance(iEnd, *iter, m_iCurrentStep);

        dNumerator += (1 - dBegin) + (1 - dEnd);

        iVirtualCommonComputationNumber++;
    }

    double dDenominator = m_cGraph.GetVertexWeightSum(iBegin, m_iCurrentStep) + m_cGraph.GetVertexWeightSum(iEnd, m_iCurrentStep);

    double dDistance = 1 - dNumerator / dDenominator;
    m_dictVirtualEdgeTempResult[edgeKey] = dDistance;
    return dDistance;
}

CommunityDetection::CommunityDetection(bool bIsWeighted, double dThreshold) {
    m_bIsWeighted = bIsWeighted;
    m_dThreshold = dThreshold;
    m_iCurrentStep = 0;
    iVirtualEdgeNumber = 0;
    iVirtualCommonComputationNumber = 0;
    iCommonComputationNumber = 0;
    iCommonEdgeNumber = 0;
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


    for (map<int, set<int>*>::iterator iter = pCommunities->begin(); iter != pCommunities->end(); iter++)
    {
        for (set<int>::iterator iterVertex = iter->second->begin(); iterVertex != iter->second->end(); iterVertex++)
        {
            out << iter->first << ' ' << *iterVertex << endl;
        }
    }

    cout << "Output Communities Complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    out.close();
    out.clear();
}


void CommunityDetection::OutputEdges(string& strFileName)
{
    map<EdgeKey, EdgeValue*>* pEdges = m_cGraph.GetAllEdges();
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

void CommunityDetection::OutputIterationResult(string & strFileName)
{
    ofstream out(strFileName.c_str(), ios::out);

    cout << "Output edges Start" << endl;

    int iLastConvergeNumber = 0;

    for (map<int, int>::iterator iter = m_dictInteration.begin(); iter != m_dictInteration.end(); iter++)
    {
        out << iter->first << " " << iter->second - iLastConvergeNumber << endl;
        iLastConvergeNumber = iter->second;
    }

    cout << "Output edges Complete" << endl;

    out.close();
    out.clear();
}

