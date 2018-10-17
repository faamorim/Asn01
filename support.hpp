//
// Created by HP User on 10/9/2018.
//
#include <cmath>
#include <limits>

#ifndef ASN01_SUPPORT_HPP
#define ASN01_SUPPORT_HPP
double tolerance = std::numeric_limits<double>::epsilon();

// Calculate if the first integer is a perfect square,
// stores the value of the square root on the second integer reference,
// and returns if it is perfect square or not.
bool IsPerfectSquare(const int i, int &a){
    int sr = (int)(std::round(sqrt(i)));
    if(sr*sr == i){
        a = sr;
        return true;
    }
    return false;
}

// Comparison to see if two doubles are close enough given a tolerance.
bool IsDoubleEquals(const double& d1, const double& d2, const double& tol = tolerance){
    double diff = fabs(d1 - d2);
    if (diff <= tol)
        return true;

    double nd1 = fabs(d1);
    double nd2 = fabs(d2);
    double largest = (nd2 > nd1) ? nd2 : nd1;

    if (diff <= largest * tol)
        return true;
    return false;
}


#endif //ASN01_SUPPORT_HPP
