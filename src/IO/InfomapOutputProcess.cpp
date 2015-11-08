//
// Created by yche on 11/1/2015.
//
#include <sstream>
#include "../DynamicDistance/Graph.h"

using namespace std;

vector<string> split(const string &s, const string &seperator) {
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size()) {
        //??????????????????
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (string_size x = 0; x < seperator.size(); ++x) {
                if (s[i] == seperator[x]) {
                    ++i;
                    flag = 0;
                    break;
                }
            }

        }

        //????????????????????????
        flag = 0;
        string_size j = i;
        while (j != s.size() && flag == 0) {
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[j] == seperator[x]) {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                ++j;
        }
        if (i != j) {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}


int main(int argc, char *argv[]) {
    string strInputFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_input_infomap.tree";
    string strOutputFileName = "E:\\projects-git\\community-detection\\dataset\\big\\road\\road_output_measurement_infomap.csv";
    ifstream in(strInputFileName.c_str(), ios::in);
    ofstream out(strOutputFileName.c_str(), ios::out);

    int lineNum = 0;
    string curStr = "";
    while (!in.eof()) {
        string line;
        getline(in, line);

        if (in && line.c_str()[0] != '#') {
            istringstream stringIn(line);
            string clusterName = "";
            double flow = -1;
            string nodeName = "";
            int nodeIndex = -1;

            stringIn >> clusterName >> flow >> nodeName >> nodeIndex;

            vector<string> splitStrs = split(clusterName, ":");
            string sBuilder = "";
            for (int i = 0; i < splitStrs.size() - 1; ++i) {
                sBuilder.append(splitStrs[i]);
            }
            clusterName = sBuilder;
            if (curStr != clusterName) {
                lineNum++;
            }
            replace(nodeName.begin(), nodeName.end(), '"', ' ');
            curStr = clusterName;
           // cout << lineNum << " " << nodeName << " " << endl;
            out << lineNum << " " << nodeName << " " << endl;
            //cout << line << endl;
        }
    }

    out.close();
    out.clear();
    in.close();
    in.clear();
    cout << "finished" << endl;
    return 0;
}