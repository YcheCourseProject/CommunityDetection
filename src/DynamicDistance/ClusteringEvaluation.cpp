#include <cmath>
#include "ClusteringEvaluation.h"

map<int, set<int>*>* ClusteringEvaluation::GenerateCommunities(const string & strFileName)
{
    ifstream in(strFileName.c_str(), ios::in);
    if (in.fail())
    {
        cout << "Fail." << endl;
        exit(0);
    }

    int i = 0;

    int iCommunitiesLabel;
    int iVertexId;

    map<int, set<int>*>* dictCommunities = new map<int, set<int>*>();
    cout << "Setup communities from file." << endl;
    const clock_t begin_time = clock();

    while (!in.eof())
    {
        in >> iCommunitiesLabel >> iVertexId;

        if (dictCommunities->count(iCommunitiesLabel) == 0)
        {
            (*dictCommunities)[iCommunitiesLabel] = new set<int>();
        }

        (*dictCommunities)[iCommunitiesLabel]->insert(iVertexId);

        if (++i % 10000 == 0)
        {
            cout << "Line Number: " << i << endl;
        }
    }

    cout << "Setup communities from file complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    in.close();
    in.clear();
    return dictCommunities;
}

map<int, set<int>*>* ClusteringEvaluation::GenerateAdjecentList(const string & strFileName)
{
    ifstream in(strFileName.c_str(), ios::in);

    if (in.fail())
    {
        cout << "Fail." << endl;
        exit(0);
    }

    int i = 0;

    int iBegin;
    int iEnd;

    map<int, set<int>*>* dictAdjacentList = new map<int, set<int>*>();

    cout << "Setup adjacent list from file." << endl;
    const clock_t begin_time = clock();

    while (!in.eof())
    {
        in >> iBegin >> iEnd;

        if (dictAdjacentList->count(iBegin) == 0)
        {
            (*dictAdjacentList)[iBegin] = new set<int>();
        }

        (*dictAdjacentList)[iBegin]->insert(iEnd);

        if (dictAdjacentList->count(iEnd) == 0)
        {
            (*dictAdjacentList)[iEnd] = new set<int>();
        }

        (*dictAdjacentList)[iEnd]->insert(iBegin);

        if (++i % 10000 == 0)
        {
            cout << "Line Number: " << i << endl;
        }
    }

    cout << "Setup adjacent list from file complete: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    in.close();
    in.clear();
    return dictAdjacentList;
}

void ClusteringEvaluation::ClearResources(map<int, set<int>*>* pTarget)
{
    if (pTarget == NULL)
        return;

    for (map<int, set<int>*>::iterator iter = pTarget->begin(); iter != pTarget->end(); iter++)
    {
        if (iter->second != NULL)
        {
            delete iter->second;
        }
    }

    delete pTarget;
}


double ClusteringEvaluation::SimplyPurity(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictGroundTruth)
{
    return Purity(dictTargetCommunities, dictGroundTruth);
}

double ClusteringEvaluation::InversePurity(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictGroundTruth)
{
    return Purity(dictGroundTruth, dictTargetCommunities);
}

double ClusteringEvaluation::Purity(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictGroundTruth)
{
    double dPurity = 0;
    int iVertexNumber = 0;

    for (map<int, set<int>*>::iterator iterTargetCommunity = dictTargetCommunities->begin(); iterTargetCommunity != dictTargetCommunities->end(); iterTargetCommunity++)
    {
        int iMaxiumCommonVertex = 0;

        for (map<int, set<int>*>::iterator iterGroundTruth = dictGroundTruth->begin(); iterGroundTruth != dictGroundTruth->end(); iterGroundTruth++)
        {
            int commonVertexNumber = CommonVertexNumber(iterTargetCommunity->second, iterGroundTruth->second);

            iMaxiumCommonVertex = iMaxiumCommonVertex > commonVertexNumber ? iMaxiumCommonVertex : commonVertexNumber;
        }

        iVertexNumber += iterTargetCommunity->second->size();

        dPurity += iMaxiumCommonVertex;
    }

    return dPurity / iVertexNumber;
}

double ClusteringEvaluation::NMI(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictGroundTruth)
{
    double** aProbabilityMatrix = new double*[dictTargetCommunities->size()];
    double* aRowProbabilitySum = new double[dictTargetCommunities->size()]{ 0 };
    double* aColumnProbabilitySum = new double[dictGroundTruth->size()]{ 0 };


    for (int i = 0; i < dictTargetCommunities->size(); ++i)
    {
        aProbabilityMatrix[i] = new double[dictGroundTruth->size()]{ 0 };
    }

    int iVerticesNumber = VerticesNumberFromCommunities(dictTargetCommunities);

    int iRowNumber = 0;
    int iColumnNumber = 0;

    for (map<int, set<int>*>::iterator iterTargetCommunity = dictTargetCommunities->begin(); iterTargetCommunity != dictTargetCommunities->end(); iterTargetCommunity++)
    {
        iColumnNumber = 0;

        for (map<int, set<int>*>::iterator iterGroundTruth = dictGroundTruth->begin(); iterGroundTruth != dictGroundTruth->end(); iterGroundTruth++)
        {
            int commonVertexNumber = CommonVertexNumber(iterTargetCommunity->second, iterGroundTruth->second);

            aProbabilityMatrix[iRowNumber][iColumnNumber] = commonVertexNumber / (double)iVerticesNumber;
            aRowProbabilitySum[iRowNumber] += aProbabilityMatrix[iRowNumber][iColumnNumber];
            aColumnProbabilitySum[iColumnNumber] += aProbabilityMatrix[iRowNumber][iColumnNumber];

            ++iColumnNumber;
        }

        ++iRowNumber;
    }

    double dMutualInformation = 0;

    for (iRowNumber = 0; iRowNumber < dictTargetCommunities->size(); ++iRowNumber)
    {
        for (iColumnNumber = 0; iColumnNumber < dictGroundTruth->size(); ++iColumnNumber)
        {
            if (aRowProbabilitySum[iRowNumber] != 0
                && aColumnProbabilitySum[iColumnNumber] != 0
                && aProbabilityMatrix[iRowNumber][iColumnNumber] != 0)
            {
                dMutualInformation += aProbabilityMatrix[iRowNumber][iColumnNumber] *
                    log2(aProbabilityMatrix[iRowNumber][iColumnNumber] / (aRowProbabilitySum[iRowNumber] * aColumnProbabilitySum[iColumnNumber]));
            }
        }
    }

    double dTargetEntropies = 0;
    for (iRowNumber = 0; iRowNumber < dictTargetCommunities->size(); ++iRowNumber)
    {
        dTargetEntropies += -aRowProbabilitySum[iRowNumber] * log2(aRowProbabilitySum[iRowNumber]);
    }

    double dGroundTruthEntropies = 0;
    for (iColumnNumber = 0; iColumnNumber < dictGroundTruth->size(); ++iColumnNumber)
    {
        dGroundTruthEntropies += -aColumnProbabilitySum[iColumnNumber] * log2(aColumnProbabilitySum[iColumnNumber]);
    }

    delete aRowProbabilitySum;
    delete aColumnProbabilitySum;
    for (int i = 0; i < dictTargetCommunities->size(); ++i)
    {
        delete aProbabilityMatrix[i];
    }
    delete aProbabilityMatrix;

    return 2 * dMutualInformation / (dTargetEntropies + dGroundTruthEntropies);
}

double ClusteringEvaluation::ARI(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictGroundTruth)
{
    int iVertexNumber = VerticesNumberFromCommunities(dictTargetCommunities);

    int iAllParisSum = TwoCombination(iVertexNumber);
    int iTargetPairsSum = TwoCombinationSum(dictTargetCommunities);
    int iGroundTruthPairsSum = TwoCombinationSum(dictGroundTruth);
    int iIntersectionParisSum = TwoCombinationSum(dictTargetCommunities, dictGroundTruth);

    double dNumerator = iIntersectionParisSum - iTargetPairsSum * iGroundTruthPairsSum / (double)iAllParisSum;
    double dDenominator = 0.5 * (iTargetPairsSum + iGroundTruthPairsSum) - iTargetPairsSum * iGroundTruthPairsSum / (double)iAllParisSum;

    return dNumerator / dDenominator;
}

double ClusteringEvaluation::RI(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictGroundTruth)
{
    int iVertexNumber = VerticesNumberFromCommunities(dictTargetCommunities);

    int iAllParisSum = TwoCombination(iVertexNumber);
    int iTargetPairsSum = TwoCombinationSum(dictTargetCommunities);
    int iGroundTruthPairsSum = TwoCombinationSum(dictGroundTruth);
    int iIntersectionParisSum = TwoCombinationSum(dictTargetCommunities, dictGroundTruth);

    return (iAllParisSum + 2 * iIntersectionParisSum - iTargetPairsSum - iGroundTruthPairsSum) / (double)iAllParisSum;
}

double ClusteringEvaluation::Modularity(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictAdjacentList)
{
    int iEdgeNumbers = 0;

    for (map<int, set<int>*>::iterator iter = dictAdjacentList->begin(); iter != dictAdjacentList->end(); iter++)
    {
        iEdgeNumbers += iter->second->size();
    }

    iEdgeNumbers /= 2;

    double dModularity = 0;

    for (map<int, set<int>*>::iterator iter = dictTargetCommunities->begin(); iter != dictTargetCommunities->end(); iter++)
    {
        double dCommunityDegree = 0;
        double dInCommunityDegree = 0;
        set<int>* pCommunities = iter->second;

        for (set<int>::iterator iterVertex = pCommunities->begin(); iterVertex != pCommunities->end(); iterVertex++)
        {
            set<int>* pNeighbours = (*dictAdjacentList)[*iterVertex];
            dCommunityDegree += pNeighbours->size();
            for (set<int>::iterator iterDest = pNeighbours->begin(); iterDest != pNeighbours->end(); iterDest++)
            {
                if (pCommunities->count(*iterDest) != 0)
                {
                    dInCommunityDegree += 0.5;
                }
            }
        }

        dModularity += dInCommunityDegree / iEdgeNumbers - pow(dCommunityDegree / (2 * iEdgeNumbers), 2);
    }

    return dModularity;
}

double ClusteringEvaluation::Ncut(map<int, set<int>*>* dictTargetCommunities, map<int, set<int>*>* dictAdjacentList)
{
    double dNcut = 0;
    int iCommunityNumber = dictTargetCommunities->size();

    for (map<int, set<int>*>::iterator iter = dictTargetCommunities->begin(); iter != dictTargetCommunities->end(); iter++)
    {
        int iCutSum = ComputeCutSum(iter->second, dictAdjacentList);
        int iVolumeSum = ComputeVolumeSum(iter->second, dictAdjacentList);

        dNcut += iCutSum / (double)iVolumeSum;
    }

    return dNcut / iCommunityNumber;
}

double ClusteringEvaluation::F_Measure(double dFirstValue, double dSecondValue)
{
    return 2 * dFirstValue * dSecondValue / ( dFirstValue + dSecondValue);
}

int ClusteringEvaluation::CommonVertexNumber(set<int>* pSrc, set<int>* pDest)
{
    int iCount = 0;

    for (set<int>::iterator iter = pSrc->begin(); iter != pSrc->end(); iter++)
    {
        iCount += pDest->count(*iter);
    }
    return iCount;
}

int ClusteringEvaluation::TwoCombinationSum(map<int, set<int>*>* pSrc)
{
    int iSum = 0;

    for (map<int, set<int>*>::iterator iter = pSrc->begin(); iter != pSrc->end(); iter++)
    {
        iSum += TwoCombination(iter->second->size());
    }

    return iSum;
}

int ClusteringEvaluation::TwoCombinationSum(map<int, set<int>*>* pTarget, map<int, set<int>*>* pGroudTruth)
{
    int iSum = 0;

    for (map<int, set<int>*>::iterator iterTargetCommunity = pTarget->begin(); iterTargetCommunity != pTarget->end(); iterTargetCommunity++)
    {
        for (map<int, set<int>*>::iterator iterGroundTruth = pGroudTruth->begin(); iterGroundTruth != pGroudTruth->end(); iterGroundTruth++)
        {
            int commonVertexNumber = CommonVertexNumber(iterTargetCommunity->second, iterGroundTruth->second);
            iSum += TwoCombination(commonVertexNumber);
        }
    }

    return iSum;
}

int ClusteringEvaluation::TwoCombination(int iNumber)
{
    if (iNumber < 2)
        return 0;

    return iNumber * (iNumber - 1) / 2;
}

double ClusteringEvaluation::AverageDegree(map<int, set<int>*>* dictAdjacentList)
{
    return  EdgesNumber(dictAdjacentList) / (double)VerticesNumberFromAdjacentList(dictAdjacentList);
}

double ClusteringEvaluation::LocalClusteringCoefficient(map<int, set<int>*>* dictAdjacentList)
{
    if (dictAdjacentList->size() == 0)
        return 0.0;

    double dClusteringCoefficient = 0;
    for (map<int, set<int>*>::iterator iter = dictAdjacentList->begin(); iter != dictAdjacentList->end(); iter++)
    {
        set<int>* pNeighbours = iter->second;

        int iNeighboursEdgeNumber = 0;

        for (set<int>::iterator iterSrc = pNeighbours->begin(); iterSrc != pNeighbours->end(); iterSrc++)
        {
            set<int>::iterator iterDest = iterSrc;
            iterDest++;

            while (iterDest != pNeighbours->end())
            {
                if ((*dictAdjacentList)[*iterSrc]->count(*iterDest) != 0)
                {
                    iNeighboursEdgeNumber++;
                }

                iterDest++;
            }
        }

        if (pNeighbours->size() > 1)
        {
            dClusteringCoefficient += iNeighboursEdgeNumber / (double)(pNeighbours->size() * (pNeighbours->size() - 1));
        }
    }

    return 2 * dClusteringCoefficient / dictAdjacentList->size();
}

int ClusteringEvaluation::VerticesNumberFromCommunities(map<int, set<int>*>* pTarget)
{
    int iVerticesNumber = 0;

    for (map<int, set<int>*>::iterator iterTargetCommunity = pTarget->begin(); iterTargetCommunity != pTarget->end(); iterTargetCommunity++)
    {
        iVerticesNumber += iterTargetCommunity->second->size();
    }

    return iVerticesNumber;
}

int ClusteringEvaluation::VerticesNumberFromAdjacentList(map<int, set<int>*>* dictAdjacentList)
{
    return dictAdjacentList->size();
}

int ClusteringEvaluation::EdgesNumber(map<int, set<int>*>* dictAdjacentList)
{
    int iEdgesNumber = 0;

    for (map<int, set<int>*>::iterator iter = dictAdjacentList->begin(); iter != dictAdjacentList->end(); iter++)
    {
        iEdgesNumber += iter->second->size();
    }

    return iEdgesNumber;
}

int ClusteringEvaluation::ComputeVolumeSum(set<int>* pSrcCommunity, map<int, set<int>*>* dictAdjacentList)
{
    int iVolumeSum = 0;

    for (set<int>::iterator iter = pSrcCommunity->begin(); iter != pSrcCommunity->end(); iter++)
    {
        iVolumeSum += (*dictAdjacentList)[*iter]->size();
    }

    return iVolumeSum;
}

int ClusteringEvaluation::ComputeCutSum(set<int>* pSrcCommunity, map<int, set<int>*>* dictAdjacentList)
{
    int iCutSum = 0;

    for (set<int>::iterator iterSrcVertex = pSrcCommunity->begin(); iterSrcVertex != pSrcCommunity->end(); iterSrcVertex++)
    {
        set<int>* pNeighbours = (*dictAdjacentList)[*iterSrcVertex];

        for (set<int>::iterator iterDestVertex = pNeighbours->begin(); iterDestVertex != pNeighbours->end(); iterDestVertex++)
        {
            if (pSrcCommunity->count(*iterDestVertex) == 0)
            {
                ++iCutSum;
            }
        }
    }

    return iCutSum;
}
