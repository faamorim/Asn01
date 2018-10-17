//
// Created by HP User on 10/7/2018.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include "matrix.hpp"
#include "support.hpp"

using namespace std;

//Prepares a matrix with the given values, number of rows and number of columns.
void Matrix::PrepareMatrix(double values[], int size, int rows, int columns) {
    if(rows * columns == 0) {
        ostringstream oss;
        oss << "Trying to create a " << rows << " by " << columns << " Matrix." << endl
            << "Unable to create a Matrix with size equal to 0.";
        throw invalid_argument(oss.str());
    }
    if(size && size != rows * columns){
        ostringstream oss;
        oss << "Trying to create a " << rows << " by " << columns
            << " Matrix passing an array of size " << size << "." << endl
            << "Incompatible array size and Matrix size. "
            << rows << " * " << columns << " = " << (rows * columns) << " != " << size << ".";
        throw invalid_argument(oss.str());
    }
    bool copy = true;
    if(values == nullptr){
        copy = false;
    }
    rows_ = rows;
    cols_ = columns;
    values_ = new double*[rows];
    for(int i = 0; i < rows; i++){
        values_[i] = new double[columns];
        if(values_[i] == nullptr){
            return;
        }
        for(int j = 0; j < columns; j++){
            if(copy){
                values_[i][j] = values[i*columns + j];
            }
            else {
                values_[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix(int size) : Matrix(size, size){}

Matrix::Matrix(double val, int size) : Matrix(val, size, size) {};

Matrix::Matrix(int rows, int columns) : Matrix(nullptr, 0, rows, columns) {}

Matrix::Matrix(double val, int rows, int columns) : Matrix(rows, columns){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            values_[i][j] = val;
        }
    }
}

Matrix::Matrix(double values[], int size){
    int msize;
    if(IsPerfectSquare(size, msize)) {
        PrepareMatrix(values, size, msize, msize);
    }
    else {
        ostringstream oss;
        oss << "Trying to create Matrix passing only an array of size " << size << "." << endl
            << "Size should be a perfect square to be able to create a Matrix.";
        throw invalid_argument(oss.str());
    }
}

Matrix::Matrix(double values[], int size, int rows, int columns){
    PrepareMatrix(values, size, rows, columns);
}

Matrix::Matrix(const Matrix& mat) : Matrix(nullptr, mat.rows_ * mat.cols_, mat.rows_, mat.cols_){
    for(int i = 0; i < mat.rows_; i++) {
        for(int j = 0; j < mat.cols_; j++){
            values_[i][j] = mat.values_[i][j];
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < rows_; i++){
        delete(values_[i]);
    }
    delete values_;
}

int Matrix::get_rows() const{
    return rows_;
}

int Matrix::get_cols() const{
    return cols_;
}

double Matrix::get_value(int r, int c) const{
    if(r > rows_ || c > cols_) {
        ostringstream oss;
        oss << "Index out of bounds." << endl
            << "The Matrix is " << get_rows() << " by " << get_cols()
            << " and program is asking for row " << get_rows() << " column " << get_cols() << ".";
        throw invalid_argument(oss.str());
    }
    return values_[r][c];
}

double Matrix::set_value(int r, int c, double v){
    if(r > rows_ || c > cols_) {
        ostringstream oss;
        oss << "Index out of bounds." << endl
            << "The Matrix is " << get_rows() << " by " << get_cols()
            << " and program is asking for row " << get_rows() << " column " << get_cols() << ".";
        throw invalid_argument(oss.str());
    }
    double last = values_[r][c];
    values_[r][c] = v;
    return last;
}

bool Matrix::Clear(){
    bool complete = true;
    for(int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            values_[i][j] = 0;
        }
    }
    return complete;
}

void Matrix::swap(Matrix& mat1, Matrix& mat2){
    using std::swap;
    swap(mat1.rows_, mat2.rows_);
    swap(mat1.cols_, mat2.cols_);
    swap(mat1.values_, mat2.values_);
}

ostream& operator<<(ostream& os, const Matrix& mat) {
    os << "[";
    for (int i = 0; i < mat.rows_; i++) {
        if(i > 0){
            os << " ";
        }
        os << "[";
        for (int j = 0; j < mat.cols_; j++) {
            os << mat.get_value(i, j);
            if (j < mat.cols_ - 1) {
                os << ", ";
            }
        }
        if (i < mat.rows_){
            os << "]";
        }
        if (i < mat.rows_ - 1) {
            os << "," << endl;
        }
    }
    os << "]";
    return os;
}

// Math operations:
// 1) ------ Operations only using Matrix
//    1.1) Unary Operations
Matrix Matrix::operator++ () {
    *this += 1;
    return *this;
}
const Matrix Matrix::operator++ (int i){
    const Matrix oldMat{*this};
    ++*this;
    return oldMat;
}
Matrix Matrix::operator-- () {
    *this -= 1;
    return *this;
}
const Matrix Matrix::operator-- (int i){
    const Matrix oldMat{*this};
    --*this;
    return oldMat;
}
Matrix Matrix::operator-(){
    return *this *= -1;
}

// 1) ------ Operations only using Matrix
//    1.2) Assignment Operation
Matrix& Matrix::operator= (Matrix const& mat){
    Matrix temp{mat};
    swap(*this, temp);
    return *this;
}
// 2) ------ Operations between Matrix and Double
//    2.1) - Scalar
Matrix operator* (const Matrix& mat, const double& mult) {
    Matrix multMat{mat};
    multMat *= mult;
    return multMat;
}

Matrix& Matrix::operator*= (const double& mult){
    for(int i = 0; i < this->rows_; i++) {
        for(int j = 0; j < this->cols_; j++){
            this->values_[i][j] = this->values_[i][j] * mult;
        }
    }
    return *this;
}

Matrix operator/ (const Matrix& mat, const double& div){
    Matrix divMat{mat};
    divMat /= div;
    return divMat;
}

Matrix& Matrix::operator/= (const double& div){
    return *this *= (1/div);
}

// 2) ------ Operations between Matrix and Double
//    2.2) - Linear
Matrix operator+ (const Matrix& mat, const double& add) {
    Matrix addMat{mat};
    addMat += add;
    return addMat;
}

Matrix& Matrix::operator+= (const double& add){
    for(int i = 0; i < this->rows_; i++) {
        for(int j = 0; j < this->cols_; j++){
            this->values_[i][j] = this->values_[i][j] + add;
        }
    }
    return *this;
}

Matrix operator- (const Matrix& mat, const double& sub){
    return mat + (-sub);
}

Matrix& Matrix::operator-= (const double& sub){
    return *this += -sub;
}

// 3) ------ Operations between Matrix and Matrix
//    3.1) - Multiplication
Matrix operator*(const Matrix& mat1, const Matrix& mat2){
    Matrix multMat{mat1};
    multMat *= mat2;
    return multMat;
}
Matrix& operator*=(Matrix& mat1, const Matrix& mat2){
    if(mat1.cols_ != mat2.rows_){
        ostringstream oss;
        oss << "Cannot multiply Matrices with incompatible dimensions." << endl
            << "LHS Matrix number of columns should be equal to RHS Matrix number of rows." << endl
            << "LHS Matrix is " << mat1.get_rows() << " by *" << mat1.get_cols()
            << "* and RHS Matrix is *" << mat2.get_rows() << "* by " << mat2.get_cols() << ".";
        throw invalid_argument(oss.str());
    }
    Matrix multMat{mat1.rows_, mat2.cols_};
    int inner = mat1.cols_;
    for(int i = 0; i < multMat.rows_; i++) {
        for(int j = 0; j < multMat.cols_; j++){
            for (int k = 0; k < inner; k++){
                multMat.values_[i][j] += mat1.values_[i][k] * mat2.values_[k][j];
            }
        }
    }
    mat1 = multMat;
    return mat1;
}

// 3) ------ Operations between Matrix and Matrix
//    3.2) - Addition / Subtraction
Matrix operator+(const Matrix& mat1, const Matrix& mat2){
    Matrix addMat{mat1};
    addMat += mat2;
    return addMat;
}
Matrix& operator+=(Matrix& mat1, const Matrix& mat2){
    return combineMatrices(mat1, mat2);
}
Matrix operator-(const Matrix& mat1, const Matrix& mat2){
    Matrix addMat{mat1};
    addMat += mat2;
    return addMat;
}
Matrix& operator-=(Matrix& mat1, const Matrix& mat2){
    return combineMatrices(mat1, mat2, true);
}

// 3) ------ Operations between Matrix and Matrix
//    3.3) - Comparison
bool operator==(const Matrix& mat1, const Matrix& mat2){
    if(mat1.rows_ != mat2.rows_ || mat1.cols_ != mat2.cols_){
        return false;
    }
    for (int i = 0; i < mat1.rows_; i++){
        for (int j = 0; j < mat1.cols_; j++){
            if(!IsDoubleEquals(mat1.values_[i][j], mat2.values_[i][j])){
                return false;
            }
        }
    }
    return true;
}
bool operator!=(const Matrix& mat1, const Matrix& mat2){
    return !(mat1==mat2);
}


// Combines two matrices (add or subtract) and returns the combined Matrix.
Matrix& combineMatrices(Matrix& mat1, const Matrix& mat2, bool sub){
    int mod = sub ? -1 : 1;
    if(mat1.get_rows() != mat2.get_rows() || mat1.get_cols() != mat2.get_cols()){
        ostringstream oss;
        oss << "Cannot combine Matrices with different dimensions." << endl
            << "LHS Matrix is " << mat1.get_rows() << " by " << mat1.get_cols()
            << " and RHS Matrix is " << mat2.get_rows() << " by " << mat2.get_cols() << ".";
        throw invalid_argument(oss.str());
    }
    int rows = mat1.get_rows();
    int cols = mat1.get_cols();
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            mat1.set_value(i, j, mat1.get_value(i, j) + mod * mat2.get_value(i, j));
        }
    }
    return mat1;
}


