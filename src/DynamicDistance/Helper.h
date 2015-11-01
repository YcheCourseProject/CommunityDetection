#pragma once
#ifndef HELPER_H
#define HELPER_H

class Helper {
private:
    static int ComputeNextStep(const int iCurrentStep);

public:
    static int UpdateStep(int &iCurrentStep);

    static int NextStep(const int iCurrentStep);
};

#endif