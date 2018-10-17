//
// Created by HP User on 10/14/2018.
//
#include "matrix.hpp"

#ifndef ASN01_MAIN_HPP
#define ASN01_MAIN_HPP

Matrix *ReadFile(const string&);
Matrix GetProbability(const Matrix&);
Matrix NormalizeCols(const Matrix&);
Matrix MarkovProcess(const Matrix&);
void PrintRank(const Matrix&);

#endif //ASN01_MAIN_HPP
