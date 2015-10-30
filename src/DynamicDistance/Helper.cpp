#include "Helper.h"

int Helper::ComputeNextStep(const int iCurrentStep)
{
    return iCurrentStep == 0 ? 1 : 0;;
}

int Helper::UpdateStep(int & iCurrentStep)
{
    iCurrentStep = ComputeNextStep(iCurrentStep);
    return iCurrentStep;
}

int Helper::NextStep(const int iCurrentStep)
{
    return ComputeNextStep(iCurrentStep);
}
