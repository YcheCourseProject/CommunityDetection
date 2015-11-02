#include "Helper.h"

int Helper::ComputeNextStep(const int iCurrentStep) {
    return iCurrentStep == 0 ? 1 : 0;;
}


void Helper::OutputEvaluationResult(const string& strFileName, map<string, double>& dictEvaluationResult)
{
    ofstream out(strFileName.c_str(), ios::out);

    for (map<string, double>::iterator iter = dictEvaluationResult.begin(); iter != dictEvaluationResult.end(); iter++)
    {
        out << iter->first << " " << iter->second << endl;
    }

    out.close();
    out.clear();
}

int Helper::UpdateStep(int & iCurrentStep)
{
    iCurrentStep = ComputeNextStep(iCurrentStep);
    return iCurrentStep;
}

int Helper::NextStep(const int iCurrentStep) {
    return ComputeNextStep(iCurrentStep);
}
