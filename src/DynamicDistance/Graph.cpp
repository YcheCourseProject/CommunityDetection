#include "Graph.h"

bool Graph::AddActualEdge(int iBegin, int iEnd, double dWeight, EdgeValue* &pNewEdgeValue)
{
    return AddEdge(iBegin, iEnd, dWeight, m_dictActualEdges, pNewEdgeValue);
}

bool Graph::AddVirtualEdge(int iBegin, int iEnd, double dWeight, EdgeValue* &pNewEdgeValue)
{
    return AddEdge(iBegin, iEnd, dWeight, m_dictVirtualEdges, pNewEdgeValue, false);
}

void Graph::UpdateActualEdge(int iBegin, int iEnd, double dNewDistance, int iStep)
{
    UpdateEdge(iBegin, iEnd, dNewDistance, iStep, m_dictActualEdges);
}

void Graph::UpdateVirtualEdge(int iBegin, int iEnd, double dNewDistance, int iStep)
{
    UpdateEdge(iBegin, iEnd, dNewDistance, iStep, m_dictVirtualEdges);
}

double Graph::ActualDistance(int iBegin, int iEnd, int iStep)
{
    return Distance(iBegin, iEnd, iStep, m_dictActualEdges);
}

double Graph::VirtualDistance(int iBegin, int iEnd, int iStep)
{
    return Distance(iBegin, iEnd, iStep, m_dictVirtualEdges);
}

double Graph::Weight(int iBegin, int iEnd)
{
    if (iBegin == iEnd)
        return 0.0;

    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (m_dictActualEdges.count(edgeKey) == 0)
    {
        return 0.0;
    }

    return m_dictActualEdges[edgeKey]->dWeight;
}

map<int, set<int>* >* Graph::FindAllConnectedComponents()
{
    set<int> setVisitedVertices;
    queue<int> que;

    map<int, set<int>* >* pResult = new map<int, set<int>* >();

    int iCommunityNumber = 0;

    for (map<int, VertexValue* >::iterator iter = m_dictVertices.begin(); iter != m_dictVertices.end(); iter++)
    {
        int iSourceVertice = iter->first;

        if (setVisitedVertices.count(iSourceVertice) == 0)
        {
            que.push(iSourceVertice);
            setVisitedVertices.insert(iSourceVertice);

            (*pResult)[++iCommunityNumber] = new set<int>();

            while (!que.empty())
            {
                int iActiveVertice = que.front();
                que.pop();

                (*pResult)[iCommunityNumber]->insert(iActiveVertice);

                set<int>* pNeighbours = m_dictVertices[iActiveVertice]->pNeighbours;

                for (set<int>::iterator iterNeighbour = pNeighbours->begin(); iterNeighbour != pNeighbours->end(); iterNeighbour++)
                {
                    EdgeKey edgeKey{iActiveVertice, *iterNeighbour};
                    if (setVisitedVertices.count(*iterNeighbour) == 0
                        && (ActualDistance(iActiveVertice, *iterNeighbour, 0) < 1
                            && ActualDistance(iActiveVertice, *iterNeighbour, 1) < 1))
                    {
                        que.push(*iterNeighbour);
                        setVisitedVertices.insert(*iterNeighbour);
                    }
                }
            }
        }
    }

    return pResult;
}

map<EdgeKey, EdgeValue*>* Graph::GetEdges()
{
    return &m_dictActualEdges;
}

set<int>* Graph::GetVertexNeighbours(int iVertexId)
{
    if (m_dictVertices.count(iVertexId) == 0)
    {
        throw new exception("No such an iVertexId.");
    }

    VertexValue* vertexValue = m_dictVertices[iVertexId];
    return m_dictVertices[iVertexId]->pNeighbours;
}

set<int>* Graph::GetCommonNeighboursOfVirtualEdge(int iBegin, int iEnd)
{
    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (m_dictVirtualEdges.count(edgeKey) == 0)
    {
        throw new exception("No such virtual edges.");
    }

    return m_dictActualEdges[edgeKey]->pCommonNeighbours;
}

Graph::~Graph()
{
    ClearVertices();
    ClearEdges(m_dictActualEdges);
    ClearEdges(m_dictVirtualEdges);
}

void Graph::AddVertex(int iBegin, int iEnd)
{
    if (m_dictVertices.count(iBegin) == 0)
    {
        m_dictVertices[iBegin] = new VertexValue();
        m_dictVertices[iBegin]->pNeighbours = new set<int>();
        m_dictVertices[iBegin]->pNeighbours->insert(iBegin);
    }

    m_dictVertices[iBegin]->pNeighbours->insert(iEnd);
}

bool Graph::AddEdge(int iBegin, int iEnd, double dWeight, map<EdgeKey, EdgeValue*>& dictEdges, EdgeValue* &pNewEdgeValue, bool bIsActual)
{
    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (dictEdges.count(edgeKey) != 0)
    {
        return false;
    }

    EdgeValue* pEdgeValue = pNewEdgeValue = dictEdges[edgeKey] = new EdgeValue();

    for (int i = 0; i < STEP_LENGTH; ++i)
    {
        pEdgeValue->aDistance[i] = 0;
    }

    pEdgeValue->dWeight = dWeight;
    pEdgeValue->pCommonNeighbours = new set<int>();
    pEdgeValue->pExclusiveNeighbours[BEGIN_POINT] = new set<int>();
    pEdgeValue->pExclusiveNeighbours[END_POINT] = new set<int>();

    if (bIsActual)
    {
        AddVertex(iBegin, iEnd);
        AddVertex(iEnd, iBegin);
    }

    return true;
}

void Graph::UpdateEdge(int iBegin, int iEnd, double dDistance, int iStep, map<EdgeKey, EdgeValue*>& dictEdges)
{
    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{iBegin, iEnd};

    if (dictEdges.count(edgeKey) == 0)
    {
        throw new exception("No Such Edges");
    }

    dictEdges[edgeKey]->aDistance[iStep] = dDistance;
}

void Graph::RefineEdgeKey(int & iBegin, int & iEnd)
{
    if (iBegin > iEnd)
    {
        swap(iBegin, iEnd);
    }
}

void Graph::ClearVertices()
{
    for (map<int, VertexValue*>::iterator iter = m_dictVertices.begin(); iter != m_dictVertices.end(); iter++)
    {
        if (iter->second != NULL)
        {
            if (iter->second->pNeighbours != NULL)
            {
                delete iter->second->pNeighbours;
                iter->second->pNeighbours = NULL;
            }

            delete iter->second;
            iter->second = NULL;
        }
    }
}

void Graph::ClearEdges(map<EdgeKey, EdgeValue*>& dictEdges)
{
    for (map<EdgeKey, EdgeValue*>::iterator iter = dictEdges.begin(); iter != dictEdges.end(); iter++)
    {
        if (iter->second != NULL)
        {
            if (iter->second->pCommonNeighbours != NULL)
            {
                delete iter->second->pCommonNeighbours;
                iter->second->pCommonNeighbours = NULL;
            }

            if (iter->second->pExclusiveNeighbours != NULL)
            {
                delete iter->second->pCommonNeighbours;
                iter->second->pCommonNeighbours = NULL;
            }

            delete iter->second;
            iter->second = NULL;
        }
    }
}

double Graph::Distance(int iBegin, int iEnd, int iStep, map<EdgeKey, EdgeValue*>& dictEdges)
{
    if (iBegin == iEnd)
        return 0;

    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (dictEdges.count(edgeKey) == 0)
    {
        throw new exception("No edge.");
    }

    return dictEdges[edgeKey]->aDistance[iStep];
}
