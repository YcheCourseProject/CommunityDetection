//
// Created by yche on 11/1/2015.
//

#include "Graph.h"
using namespace std;

void insert2Map(int pKey, int pNeighbor, map<int,vector<int>> & m_pNeighbors){
    map<int, vector<int>>::iterator iter;
    iter = m_pNeighbors.find(pKey);
    if(iter == m_pNeighbors.end()){
        vector<int> neighbors;
        neighbors.push_back(pNeighbor);
        m_pNeighbors.insert(make_pair(pKey, neighbors));
    }
    else{
        iter -> second.push_back(pNeighbor);
    }
}

int main(int argc, char * argv[])
{
    string strInputFileName = "E:\\projects-git\\community-detection\\dataset\\small\\polbooks\\polbooks_edges_input.csv";
    string strOutputFileName = "E:\\projects-git\\community-detection\\dataset\\small\\polbooks\\polbooks_edges.input_metis.csv";
    ifstream in(strInputFileName.c_str(), ios::in);
    ofstream out(strOutputFileName.c_str(), ios::out);

    map<int, vector<int>> m_pNeighbors;

    int nEdge=0;
    bool hasZero=false;
    while(!in.eof()){
        int tempInt=-1;
        in >> tempInt;
        if(tempInt ==0){
            hasZero = true;
            break;
        }
    }

    in.clear();
    in.seekg(0, ios::beg);

    while (!in.eof()) {
        int pBegin=-1;
        int pEnd=-1;
        in >> pBegin;
        in >> pEnd;
        if(pBegin == -1){
            cout << nEdge;
            break;
        }
        if(hasZero == true){
            pBegin++;
            pEnd++;
        }

        insert2Map(pBegin, pEnd, m_pNeighbors);
        nEdge++;
        insert2Map(pEnd, pBegin, m_pNeighbors);
    }

    cout << "finished in";

    out << m_pNeighbors.size() <<' '<< nEdge << endl;
    for(map<int, vector<int>>::iterator iter = m_pNeighbors.begin(); iter != m_pNeighbors.end(); iter++)
    {
        vector<int>  neighbors =  iter->second;
        for(vector<int>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++){
            out << *iter <<' ';
        }
        out << endl;
    }

    in.close();
    in.clear();
    out.close();
    out.clear();

    cout <<"finished";
    return 0;
}