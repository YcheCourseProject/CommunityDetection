#include "Graph.h"

bool Graph::AddEdge(int iBegin, int iEnd, double dWeight, EdgeValue* &pNewEdgeValue)
{
    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (m_dictEdges.count(edgeKey) != 0)
    {
        return false;
    }

    EdgeValue* pEdgeValue = pNewEdgeValue = m_dictEdges[edgeKey] = new EdgeValue();

    for (int i = 0; i < STEP_LENGTH; ++i)
    {
        pEdgeValue->aDistance[i] = 0;
    }

    pEdgeValue->dWeight = dWeight;
    pEdgeValue->pCommonNeighbours = new set<int>();
    pEdgeValue->pExclusiveNeighbours[BEGIN_POINT] = new set<int>();
    pEdgeValue->pExclusiveNeighbours[END_POINT] = new set<int>();
    AddVertex(iBegin, iEnd);
    AddVertex(iEnd, iBegin);

    return true;
}

void Graph::UpdateEdge(int iBegin, int iEnd, double dNewDistance, int iStep)
{
    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (m_dictEdges.count(edgeKey) == 0)
    {
        throw new exception("No Such Edges");
    }

    m_dictEdges[edgeKey]->aDistance[iStep] = dNewDistance;
}

double Graph::Distance(int iBegin, int iEnd, int iStep)
{
    if (iBegin == iEnd)
        return 0;

    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (m_dictEdges.count(edgeKey) == 0)
    {
        throw new exception("No edge.");
    }

    return m_dictEdges[edgeKey]->aDistance[iStep];
}

double Graph::Weight(int iBegin, int iEnd)
{
    if (iBegin == iEnd)
        return 0.0;

    RefineEdgeKey(iBegin, iEnd);

    EdgeKey edgeKey{ iBegin, iEnd };

    if (m_dictEdges.count(edgeKey) == 0)
    {
        return 0.0;
    }

    return m_dictEdges[edgeKey]->dWeight;
}

double Graph::GetVertexWeightSum(int iVertexId, int iStep)
{
    if (m_dictVertices.count(iVertexId) == 0)
    {
        throw new exception("Vertex is not exist.");
    }

    return m_dictVertices[iVertexId]->aWeightSum[iStep];
}

void Graph::AddVertexWeight(int iVertexId, double dDistance, int iStep)
{
    if (m_dictVertices.count(iVertexId) == 0)
    {
        throw new exception("Vertex is not exist.");
    }

    m_dictVertices[iVertexId]->aWeightSum[iStep] += 1 - dDistance;
}

void Graph::ClearVertexWeight(int iStep)
{
    for (map<int, VertexValue*>::iterator iter = m_dictVertices.begin(); iter != m_dictVertices.end(); iter++)
    {
        iter->second->aWeightSum[iStep] = 0;
    }
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
                        && (Distance(iActiveVertice, *iterNeighbour, 0) < 1
                            && Distance(iActiveVertice, *iterNeighbour, 1) < 1))
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

map<EdgeKey, EdgeValue*>* Graph::GetAllEdges()
{
    return &m_dictEdges;
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

Graph::~Graph()
{
    ClearVertices();
    ClearEdges();
}

void Graph::AddVertex(int iBegin, int iEnd)
{
    if (m_dictVertices.count(iBegin) == 0)
    {
        m_dictVertices[iBegin] = new VertexValue();
        m_dictVertices[iBegin]->aWeightSum[0] = 0;
        m_dictVertices[iBegin]->aWeightSum[1] = 0;
        m_dictVertices[iBegin]->pNeighbours = new set<int>();
        
        m_dictVertices[iBegin]->pNeighbours->insert(iBegin);
    }

    m_dictVertices[iBegin]->pNeighbours->insert(iEnd);
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

void Graph::ClearEdges()
{
    for (map<EdgeKey, EdgeValue*>::iterator iter = m_dictEdges.begin(); iter != m_dictEdges.end(); iter++)
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
