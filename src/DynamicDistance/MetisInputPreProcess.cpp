//
// Created by yche on 11/1/2015.
//

#include "Graph.h"

using namespace std;

void insert2Map(int pKey, int pNeighbor, map<int, vector<int>> &m_pNeighbors) {
    map<int, vector<int>>::iterator iter;
    iter = m_pNeighbors.find(pKey);
    if (iter == m_pNeighbors.end()) {
        vector<int> neighbors;
        neighbors.push_back(pNeighbor);
        m_pNeighbors.insert(make_pair(pKey, neighbors));
    }
    else {
        iter->second.push_back(pNeighbor);
    }
}

bool containsZero(ifstream &in) {
    int nEdge = 0;
    bool hasZero = false;
    while (!in.eof()) {
        int tempInt = -1;
        in >> tempInt;
        if (tempInt == 0) {
            hasZero = true;
            break;
        }
    }
    in.clear();
    in.seekg(0, ios::beg);
    return hasZero;
}

map<int,int> calPNameIndexMap(map<int, vector<int>> & m_pNeighbors){
    int i=1;
    map<int, int> m_pNameIndex;
    for(map<int, vector<int>>::iterator iter = m_pNeighbors.begin(); iter != m_pNeighbors.end(); iter++){
        int pName = iter ->first;
        m_pNameIndex.insert(make_pair(pName, i));
        i++;
    }
    return m_pNameIndex;
}

void readFile2Memory(map<int, vector<int>> & m_pNeighbors, ifstream & in, int &nEdge){
    while (!in.eof()) {
        int pBegin = -1;
        int pEnd = -1;
        in >> pBegin;
        in >> pEnd;
        if (pBegin == -1) {
            break;
        }
        insert2Map(pBegin, pEnd, m_pNeighbors);
        insert2Map(pEnd, pBegin, m_pNeighbors);
        nEdge++;
    }
    cout << "Finish LoadIn Data" << endl;

}

void writeMapInfo2FIle(map<int, int> & m_pNameIndex, ofstream & m_out){

    m_out << "Original Name" << '\t' << "Index Val" << endl;
    for(map<int,int>::iterator iter = m_pNameIndex.begin(); iter != m_pNameIndex.end(); iter++){
        m_out << iter -> first << ' ' << iter -> second << endl;
    }
    m_out.close();
    m_out.clear();
}

void writeMetisFormatFile(map<int, vector<int>> & m_pNeighbors,  map<int, int> &m_pNameIndex, int & nEdge, ofstream & out){
    out << m_pNeighbors.size() << ' ' << nEdge << endl;
    int i = 1;
    for (map<int, vector<int>>::iterator iter = m_pNeighbors.begin(); iter != m_pNeighbors.end(); iter++) {
//        cout << m_pNameIndex.find(iter->first - i) -> second<< endl;
        i++;
        vector<int> neighbors = iter->second;
        for (vector<int>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++) {
            out << m_pNameIndex.find(*iter) ->second << ' ';
        }
        out << endl;
    }
    out.close();
    out.clear();
}


int main(int argc, char *argv[]) {
    string strInputFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_input.csv";
    string strOutputFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_input_metis.csv";
    string strMapFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_nodes_map.csv";
    ifstream in(strInputFileName.c_str(), ios::in);
    ofstream out(strOutputFileName.c_str(), ios::out);
    ofstream m_out(strMapFileName.c_str(), ios::out);
    map<int, vector<int>> m_pNeighbors;
    map<int, int> m_pNameIndex;         //map(name,index)
    int nEdge = 0;

    readFile2Memory(m_pNeighbors, in, nEdge);
    m_pNameIndex = calPNameIndexMap(m_pNeighbors);
    writeMapInfo2FIle(m_pNameIndex, m_out);
    writeMetisFormatFile(m_pNeighbors, m_pNameIndex, nEdge, out);


    cout << "finished";
    return 0;
}