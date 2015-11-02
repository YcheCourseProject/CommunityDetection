//
// Created by yche on 11/2/2015.
//
#include "../DynamicDistance/Graph.h"
using namespace std;

int main(int argc, char* argv[])
{
    string strInputFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_input_infomap.tree";
    string strOutputFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_output_measurement_infomap.csv";
    ifstream in(strInputFileName.c_str(), ios::in);
    ofstream out(strOutputFileName.c_str(), ios::out);

    out.close();
    out.clear();
    in.close();
    in.clear();
    cout << "finished" << endl;
}

