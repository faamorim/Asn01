//
// Created by HP User on 10/14/2018.
//

#include <iostream>
#include <cmath>
#include "matrixtests.hpp"
#include "support.hpp"
#include "matrix.hpp"

using namespace std;

int maxTest = 6;

void test(int mode) {
    switch(mode){
        case 1:
            testCreate();
            break;
        case 2:
            testMultDivDouble();
            break;
        case 3:
            testMultMat();
            break;
        case 4:
            testAssign();
            break;
        case 5:
            testAddSub();
            break;
        case 6:
            testEquals();
            break;
    }
}

void testAll(){
    for(int t = 0; t <= maxTest; t++){
        test(t);
    }
}

void testCreate(){
    //Test: Create Arrays:
    cout << "Test: Create Arrays:" << endl;

    Matrix m1{2};
    cout << "m1" << endl << m1 << endl;

    Matrix m2{2,3};
    cout << "m2" << endl << m2 << endl;

    Matrix m3{new double[9] {0.11, 0.12, 0.13, 0.21, 0.22, 0.23, 0.31, 0.32, 0.33}, 9};
    cout << "m3" << endl << m3 << endl;

    Matrix m4{nullptr, 0};
    cout << "m4" << endl << m4 << endl;

    Matrix m5{new double[6] {1.1, 1.2, 1.3, 2.1, 2.2, 2.3},6 , 2, 3};
    cout << "m5" << endl << m5 << endl;

    Matrix m6{new double[2] {1, 2}, 2};
    cout << "m6" << endl << m6 << endl;
}

void testMultDivDouble(){
    //Test: Multiply and Divide Array by a Double:
    cout << "Test: Multiply and Divide Array by a Double:" << endl;
    Matrix m23{new double[6] {1.1, 1.2, 1.3, 2.1, 2.2, 2.3},6 , 2, 3};
    cout << "m23" << endl << m23 << endl;
    Matrix mm23 = m23 * 10;
    cout << "mm23" << endl << mm23 << endl;
    cout << "m23" << endl << m23 << endl;
    Matrix dm23 = mm23 / 3;
    cout << "dm23" << endl << dm23 << endl;
    mm23 /= 5;
    cout << "mm23" << endl << mm23 << endl;
}

void testMultMat(){
    //Test: Multiply and Divide Array by another Array:
    cout << "Test: Multiply and Divide Array by another Array:" << endl;
    Matrix m25{new double[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10, 2, 5};
    Matrix m51{new double[5]{1, 2, 3, 4, 5}, 5, 5, 1};
    Matrix m = m25 * m51;
    cout << "m25" << endl << m25 << endl;
    cout << "m51" << endl << m51 << endl;
    cout << "m" << endl << m << endl;
}

void testAssign(){
    //Test: Assign a matrix to another matrix using the assign operation
    cout << "Test: Assign a matrix to another matrix using the assign operation" << endl;
    Matrix m25{new double[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10, 2, 5};
    Matrix m51{new double[5]{1, 2, 3, 4, 5}, 5, 5, 1};
    cout << "m25" << endl << m25 << endl;
    cout << "m51" << endl << m51 << endl;
    m25 = m51;
    cout << "m25" << endl << m25 << endl;
    cout << "m51" << endl << m51 << endl;
}

void testAddSub(){
    Matrix m23{new double[6]{1,2,3,4,5,6}, 6, 2, 3};
    Matrix m32{new double[6]{1,2,3,4,5,6}, 6, 3, 2};
    cout << "m23" << endl << m23 << endl;
    cout << "m32" << endl << m32 << endl;
    m23 += 1;
    m32--;
    cout << "m23" << endl << m23 << endl;
    cout << "m32" << endl << m32 << endl;
    Matrix m23b = m23 + 10;
    Matrix m23c = m23 *2;
    Matrix m32b = m32 + 10;
    Matrix m32c = m32 *2;
    cout << "m23b" << endl << m23b << endl;
    cout << "m32b" << endl << m32b << endl;
    cout << "m23c" << endl << m23c << endl;
    cout << "m32c" << endl << m32c << endl;
    m23 = m23b + m23c;
    m32 -= m32c;
    m32 = m32 + m32b;
    cout << "m23" << endl << m23 << endl;
    cout << "m32" << endl << m32 << endl;
}

void testEquals(){
    bool fullprint = false;
    Matrix mat(new double[16]{1'000'000'000.0, 1'000'000.0, 1'000.0, 1.0, 0.1, 0.000'1, 0.000'000'1, 0.000'000'000'1, (1.0/3), (1.0/7), (1.0/11), (1.0/13), (1.0/17), (1.0/19), (1.0/23), (1.0/29)}, 16, 4, 4);
    Matrix copy(mat);
    Matrix equal(mat);
    Matrix almostEqual(mat);
    Matrix shouldBeEqual(mat);
    Matrix notEqual(mat);
    Matrix inverse(mat);
    Matrix notEvenClose(mat);
    Matrix totallyDifferent(new double[2]{1,2}, 2, 1, 2);
    equal *= 1'000'000'000'000'000.0;
    equal *= 5'000'000.0;
    equal *= 3'000.0;
    equal /= 15'000'000'000'000'000'000'000'000.0;
    almostEqual *= (1 + 0.5 * tolerance);
    shouldBeEqual *= 271717263;
    shouldBeEqual += 271717263;
    shouldBeEqual /= 271717263;
    shouldBeEqual--;
    inverse *= -1;
    notEvenClose *= 0;
    notEqual *= (1+tolerance);
    cout << "Matrix: " << endl << mat << endl << (mat==mat ? "is equal" : "is NOT equal") << endl << endl;
    cout << "Copy: " << endl << copy << endl << (copy==mat ? "is equal" : "is NOT equal") << endl << endl;
    cout << "Equal: " << endl << equal << endl << (mat==equal ? "is equal" : "is NOT equal") << endl << endl;
    cout << "AlmostEqual " << endl << almostEqual << endl << (mat==almostEqual ? "is equal" : "is NOT equal") << endl << endl;
    cout << "ShouldBeEqual " << endl << shouldBeEqual << endl << (mat==shouldBeEqual ? "is equal" : "is NOT equal") << endl << endl;
    cout << "Inverse " << endl << inverse << endl << (mat==inverse ? "is equal" : "is NOT equal") << endl << endl;
    cout << "notEqual " << endl << notEqual << endl << (mat==notEqual ? "is equal" : "is NOT equal") << endl << endl;
    cout << "notEvenClose " << endl << notEvenClose << endl << (mat==notEvenClose ? "is equal" : "is NOT equal") << endl << endl;
    cout << "totalyDifferent " << endl << totallyDifferent << endl << (mat==totallyDifferent ? "is equal" : "is NOT equal") << endl << endl;
}
