#include <iostream>
#include <iomanip>
#include <fstream>

#include "matrix.hpp"
#include "matrix.cpp"
#include "support.hpp"
#include "matrixtests.cpp"
#include "main.hpp"

using namespace std;
string fileName = "connectivity.txt";

int main() {
    //testAll();
    Matrix *connMat = ReadFile(fileName);
    if(connMat == nullptr){
        cerr << "Unable to load file " << fileName << "." << endl;
        return 1;
    }
    try {
        Matrix probMat = GetProbability(*connMat);
        double probFactor = 0.85;
        Matrix Q{1.0 / connMat->get_rows(), connMat->get_rows(), connMat->get_cols()};
        Matrix *transitMat = new Matrix((probMat * probFactor) + (Q * (1 - probFactor)));
        Matrix rank = MarkovProcess(*transitMat);
        PrintRank(rank);
    }
    catch(invalid_argument& e){
        cerr << e.what();
    }
    return 0;
}

// Tries to read a file with given fileName.
// Returns a Square Matrix Pointer on success,
// or a null pointer if unable to read file.
Matrix *ReadFile(const string& fileName){
    ifstream file{fileName, ios_base::in};
    if(!file.is_open()) {
        cout << "Unable to open file " << fileName << endl;
        return nullptr;
    }
    double d;
    int count = 0;
    int increment = 100;
    int size = 0;
    double *list = new double[size];
    while (file >> d) {
        if(count >= size) {
            double *newList = new double[size + increment];
            for(int i = 0; i < size; i++) {
                newList[i] = list[i];
            }
            double *oldList = list;
            list = newList;
            delete[] oldList;
            size += increment;
        }
        list[count ++] = d;
    }
    Matrix *matrix = new Matrix{list, count};
    delete[] list;
    return matrix;
}

// Returns the Probability Matrix given the input Matrix
Matrix GetProbability(const Matrix& mat){
    Matrix probMat{mat};
    for(int j = 0; j < mat.get_cols(); j++){
        int count = 0;
        for(int i = 0; i < mat.get_rows(); i++){
            count += mat.get_value(i, j);
        }
        for(int i = 0; i < mat.get_rows(); i++){
            if(count == 0){
                probMat.set_value(i, j, 1.0/mat.get_rows());
            }
            else {
                probMat.set_value(i, j, mat.get_value(i,j)/count);
            }
        }
    }
    return probMat;
}

// The Markov process to determine the rank of the pages given a Transition Matrix.
// Return the Normalized Rank Matrix.
Matrix MarkovProcess(const Matrix& mat){
    Matrix rank{1.0, mat.get_rows(), 1};
    Matrix oldRank{rank};
    do{
        oldRank = rank;
        rank = mat * rank;
    }while (rank != oldRank);

    rank = NormalizeCols(rank);
    return rank;
}

// Returns the Column Normalized version of the input Matrix
Matrix NormalizeCols(const Matrix& mat){
    double sum = 0;
    Matrix norm{mat};
    for(int i = 0; i < norm.get_rows(); i++){
        sum += norm.get_value(i, 0);
    }
    norm /= sum;
    return norm;
}

// Print the Ranks given a Rank Matrix.
void PrintRank(const Matrix& mat){
    int precision = 2;
    cout << fixed << setprecision(precision);
    int pageId = 0;
    char baseCharId = 'A';
    int pagesCount = mat.get_rows();
    bool useChar = false;

    if(pagesCount <= 26){
        useChar = true;
    }
    for (int i = 0; i < pagesCount; i++) {
        cout << "Page ";
        if(useChar){
            cout << (char)(baseCharId + pageId);
        }
        else {
            cout << pageId;
        }
        cout << ": " << setw(precision+3) << (mat.get_value(i, 0) * 100) << "%" << endl;
        pageId++;
    }
}
