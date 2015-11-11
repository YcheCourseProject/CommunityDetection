#pragma once
#ifndef HELPER_H
#define HELPER_H
#include <fstream>
#include <map>
#include <string>
using namespace std;

class Helper {
private:
    static int ComputeNextStep(const int iCurrentStep);

public:
    static int UpdateStep(int &iCurrentStep);

    static int NextStep(const int iCurrentStep);
    static void OutputEvaluationResult(const string& strFileName, map<string, double>& dictEvaluationResult);
};

#endif