//
// Created by HP User on 10/7/2018.
//
using namespace std;

#ifndef ASN01_MATRIX_HPP
#define ASN01_MATRIX_HPP


class Matrix {
private:
    int rows_;
    int cols_;
    double** values_;
    void PrepareMatrix(double[], int, int, int);
public:
    Matrix(int);
    Matrix(double, int);
    Matrix(int, int);
    Matrix(double, int, int);
    Matrix(double[], int);
    Matrix(double[], int, int, int);
    Matrix(const Matrix&);
    ~Matrix();

    int get_rows() const;
    int get_cols() const;
    double set_value(int, int, double);
    double get_value(int, int) const;
    bool Clear();

    void swap(Matrix&, Matrix&);

    friend ostream& operator<<(ostream&, const Matrix&);

    // Math operations:
    // 1) ------ Operations only using Matrix
    //    1.1) Unary Operations
    Matrix operator++();
    const Matrix operator++(int);
    Matrix operator--();
    const Matrix operator--(int);
    Matrix operator-();
    //    1.2) Assignment Operation
    Matrix& operator=(Matrix const& mat);
    // 2) ------ Operations between Matrix and Double
    //    2.1) - Scalar
    friend Matrix operator*(const Matrix&, const double&);
    Matrix& operator*=(const double&);
    friend Matrix operator/(const Matrix&, const double&);
    Matrix& operator/=(const double&);
    //    2.2) - Linear
    friend Matrix operator+(const Matrix&, const double&);
    Matrix& operator+=(const double&);
    friend Matrix operator-(const Matrix&, const double&);
    Matrix& operator-=(const double&);
    // 3) ------ Operations between Matrix and Matrix
    //    3.1) - Multiplication / "Division"
    friend Matrix operator*(const Matrix&, const Matrix&);
    friend Matrix& operator*=(Matrix&, const Matrix&);
    //    3.2) - Addition / Subtraction
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend Matrix& operator+=(Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);
    friend Matrix& operator-=(Matrix&, const Matrix&);
    //    3.3) - Comparison
    friend bool operator==(const Matrix&, const Matrix&);
    friend bool operator!=(const Matrix&, const Matrix&);

};

Matrix& combineMatrices(Matrix&, const Matrix&, bool = false);

#endif //ASN01_MATRIX_HPP
