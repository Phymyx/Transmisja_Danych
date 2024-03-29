// LAB12.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <complex>
#include <fstream>
#include <math.h>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

const int paczka11 = 11;

string S2BS(string in)
{
	string out = "";
	int n = in.length();
	string bits = "";

	for (int i = 0; i < n; i++)
	{
		int wartosc = int(in[i]);
		bits = "";

		while (wartosc > 0)
		{
			if (wartosc % 2)
			{
				bits += '1';
			}
			else
			{
				bits += '0';
			}
			wartosc = wartosc / 2;
		}
		reverse(bits.begin(), bits.end());
		out += bits;
	}
	return out;

}

int* s2ch(string in, int B)
{
	//cout << "s2ch: ";

	int * data = new int[B];

	for (int i = 0; i < B; i++)
	{
		if (in[i] == '1')
		{
			data[i] = 1;
		}
		else
		{
			data[i] = 0;
		}

		//cout << data[i];
	}

	//cout << endl;


	return data;
}



int* Hamming15(int* in)
{
	int* b = new int[11];
	int* c1 = new int[15];

	cout << "pierwsze 11 bity: ";

	for (int i = 0; i < paczka11; i++)
	{
		b[i] = in[i];
		cout << b[i];
	}

	cout << endl;

	MatrixXd matrixIdentity1;
	matrixIdentity1.setIdentity(paczka11, paczka11);
	cout << "macierz I: ";
	cout << "\n \n" << matrixIdentity1 << endl;

	MatrixXd matrixb(1, 11);
	//matrixb << 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0;
	//matrixb << 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0;
	matrixb << b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10];

	//cout << endl << "b: ";
	//cout << "\n \n" << matrixb << endl;
	
	MatrixXd matrixP(11, 4);
	matrixP << 1, 1, 0, 0,
		1, 0, 1, 0,
		0, 1, 1, 0,
		1, 1, 1, 0,
		1, 0, 0, 1,
		0, 1, 0, 1,
		1, 1, 0, 1,
		0, 0, 1, 1,
		1, 0, 1, 1,
		0, 1, 1, 1,
		1, 1, 1, 1;

	cout << endl << "macierz P: ";
	cout << "\n \n" << matrixP << endl;

	MatrixXd matrixG(matrixP.rows(), matrixP.cols() + matrixIdentity1.cols());
	matrixG << matrixP, matrixIdentity1;

	cout << endl << "macierz G: ";
	cout << "\n \n" << matrixG << endl;
	
	MatrixXd c = matrixb * matrixG;

	cout << endl << "c: ";
	cout << "\n \n" << c << endl;


	double *vc = c.data();

	for (int i = 0; i < 15; i++)
	{
		c1[i] = vc[i];
	}
	cout << endl;

	cout << endl << "c po mod2: ";
	for (int i = 0; i < 15; i++)
	{
		c1[i] = c1[i]%2;
		cout << c1[i];
	}
	cout << endl;
		
	return c1;
}

int* dekHamming15(int* in)
{
	int* s1 = new int[4];
	int* bp = new int[11];

	MatrixXd matrixIdentity2;
	matrixIdentity2.setIdentity(4, 4);
	cout << endl << "macierz In-k: ";
	cout << "\n \n" << matrixIdentity2 << endl;

	MatrixXd matrixP(11, 4);
	matrixP << 1, 1, 0, 0,
		1, 0, 1, 0,
		0, 1, 1, 0,
		1, 1, 1, 0,
		1, 0, 0, 1,
		0, 1, 0, 1,
		1, 1, 0, 1,
		0, 0, 1, 1,
		1, 0, 1, 1,
		0, 1, 1, 1,
		1, 1, 1, 1;

	MatrixXd Pt;
	Pt = matrixP.transpose();
	cout << "\n\n macierz P transponowana: \n\n " << Pt << endl;

	MatrixXd matrixH(matrixIdentity2.rows(), matrixIdentity2.cols() + Pt.cols());
	matrixH << matrixIdentity2, Pt;

	cout << endl << "macierz H: ";
	cout << "\n \n" << matrixH << endl;

	MatrixXd Ht;
	Ht = matrixH.transpose();
	cout << "\n\n macierz H transponowana: \n\n " << Ht << endl;

	MatrixXd matrixc(1, 15);
	//matrixb << 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0;
	//matrixb << 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0;
	matrixc << in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7], in[8], in[9], in[10], in[11], in[12], in[13], in[14];

	cout << endl << "c: ";
	cout << "\n \n" << matrixc << endl;

	MatrixXd s = matrixc * Ht;

	cout << endl << "s: ";
	cout << "\n \n" << s << endl;

	double *vs = s.data();

	for (int i = 0; i < 4; i++)
	{
		s1[i] = vs[i];
	}
	cout << endl;

	cout << endl << "s po mod2: ";
	for (int i = 0; i < 4; i++)
	{
		s1[i] = s1[i] % 2;
		cout << s1[i];
	}
	cout << endl;

	int S = s1[0] + s1[1] * 2 + s1[2] * 4 + s1[3] * 8;

	cout << "S: " << S << endl;


	if (S == 0)
	{
		/*
		bp[0] = in[2];//3
		bp[1] = in[4];//5
		bp[2] = in[5];//6 // tutaj powinno byc 0 a jest 1
		bp[3] = in[6];//7
		bp[4] = in[8];//9
		bp[5] = in[9];//10
		bp[6] = in[10];//11
		bp[7] = in[11];//12
		bp[8] = in[12];//13
		bp[9] = in[13];//14
		bp[10] = in[14];//15
		*/
		bp[0] = in[4];//x3
		bp[1] = in[5];//x5
		bp[2] = in[6];//x6
		bp[3] = in[7];//x7
		bp[4] = in[8];//x9
		bp[5] = in[9];//x10
		bp[6] = in[10];//x11
		bp[7] = in[11];//x12
		bp[8] = in[12];//x13
		bp[9] = in[13];//x14
		bp[10] = in[14];//x15
		cout << "b': ";

		for (int i = 0; i < paczka11; i++)
		{
			cout << bp[i];
		}

		cout << endl;
	}
	else
	{
		cout << "Wystapil blad na x" << S << endl;
		if (S == 4)
		{
			in[S - 2] = !in[S - 2];
		}
		else if (S == 8)
		{
			in[S - 5] = !in[S - 5];
		}
		else if (S == 3)
		{
			in[S + 1] = !in[S + 1];
		}
		else if (S == 5)
		{
			in[S] = !in[S];
		}
		else if (S == 6)
		{
			in[S] = !in[S];
		}
		else if (S == 7)
		{
			in[S] = !in[S];
		}
		else
		{
			in[S - 1] = !in[S - 1];
		}
		cout << "Hamming(15, 11) po naprawie bitu: ";

		for (int j = 0; j < 15; j++)
		{
			cout << in[j];
		}
		cout << endl;

		bp[0] = in[4];//x3
		bp[1] = in[5];//x5
		bp[2] = in[6];//x6
		bp[3] = in[7];//x7
		bp[4] = in[8];//x9
		bp[5] = in[9];//x10
		bp[6] = in[10];//x11
		bp[7] = in[11];//x12
		bp[8] = in[12];//x13
		bp[9] = in[13];//x14
		bp[10] = in[14];//x15

		cout << "b': ";

		for (int i = 0; i < paczka11; i++)
		{
			cout << bp[i];
		}

		cout << endl;
	}

	return 0;
}

void Negacja(int* &in, int index)
{
	in[index - 1] = !in[index - 1];
}

int main()
{
	
	string str = S2BS("ab");
	cout << "ab" << endl;
	cout << str << endl;

	cout << "dl str: ";
	int B = str.length();
	cout << B << endl;

	
	int * bity = s2ch(str, B);

	int * Hamming1511 = Hamming15(bity);

	int * dekHamming1511 = dekHamming15(Hamming1511);

	int index = 5;
	cout << endl << "Negacja " << index << " bitu" << endl;
	Negacja(Hamming1511, index);

	cout << "Hamming(15, 11) po negacji: ";

	for (int j = 0; j < 15; j++)
	{
		cout << Hamming1511[j];
	}
	cout << endl;

	int * DekHamming2 = dekHamming15(Hamming1511);
	
	/*
	Matrix <float, 3, 3> matrixA;
	matrixA.setZero();
	cout << matrixA << endl;

	Matrix3f matrixA1;
	matrixA1.setZero();

	cout << "\n" << matrixA1 << endl;

	Matrix <float, Dynamic, Dynamic> matrixB;

	MatrixXf matrixB1;

	MatrixXd matrixC(10, 10);

	MatrixXd matrixC1(2, 2);
	matrixC1(0, 0) = 1;
	matrixC1(0, 1) = 2;
	matrixC1(1, 0) = 3;
	matrixC1(1, 1) = 4;

	cout << endl << matrixC1 << endl;

	Matrix4f matrixD;
	matrixD << 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16;
	cout << endl << matrixD << endl;

	Matrix3f matrixD1;
	matrixD1.resize(3, 3);
	matrixD1.setZero(3, 3);
	cout << endl << matrixD1 << endl;

	// setting matrix entries - two approaches
	int rowNumber = 5;
	int columnNumber = 5;

	// matrix of zeros
	MatrixXf matrix1zeros;
	matrix1zeros = MatrixXf::Zero(rowNumber, columnNumber);
	cout << "\n \n" << matrix1zeros << endl;
	// another option:
	MatrixXf matrix1zeros1;
	matrix1zeros1.setZero(rowNumber, columnNumber);
	cout << "\n \n" << matrix1zeros1 << endl;

	//matrix of ones
	MatrixXf matrix1ones;
	matrix1ones = MatrixXf::Ones(rowNumber, columnNumber);
	cout << "\n \n" << matrix1ones << endl;
	//another option
	MatrixXf matrix1ones1;
	matrix1ones1.setOnes(rowNumber, columnNumber);
	cout << "\n \n" << matrix1ones1 << endl;

	//matrix of constants
	float value = 1.1;
	MatrixXf matrix1const;
	matrix1const = MatrixXf::Constant(rowNumber, columnNumber, value);
	cout << "\n \n" << matrix1const << endl;
	//another option
	MatrixXf matrix1const1;
	matrix1const1.setConstant(rowNumber, columnNumber, value);
	cout << "\n \n" << matrix1const1 << endl;


	//identity matrix, two approaches

	rowNumber = 10;
	columnNumber = 10;

	MatrixXd matrixIdentity;
	matrixIdentity = MatrixXd::Identity(rowNumber, columnNumber);
	cout << "\n \n" << matrixIdentity << endl;

	MatrixXd matrixIdentity1;
	matrixIdentity1.setIdentity(rowNumber, columnNumber);
	cout << "\n \n" << matrixIdentity1 << endl;

	//accessing matrix blocks
	MatrixXd matrixV(4, 4);
	matrixV << 101, 102, 103, 104,
		105, 106, 107, 108,
		109, 110, 111, 112,
		113, 114, 115, 116;
	//access the matrix composed of 1:2 rows and 1:2 columns of matrixV
	MatrixXd matrixVpartition = matrixV.block(0, 0, 2, 2);
	cout << "\n \n" << matrixVpartition << endl;

	MatrixXd matrixVpartition2 = matrixV.block(1, 1, 2, 2);
	cout << "\n \n" << matrixVpartition2 << endl;


	//accessing columns and rows of a matrix

	cout << "\n\n" << "Row 1 of matrixV is \n " << matrixV.row(0);
	cout << "\n\n" << "Column 1 of matrixV is \n" << matrixV.col(0);

	//create a diagonal matrix out of a vector
	Matrix <double, 3, 1> vector1;
	vector1 << 1, 2, 3;
	MatrixXd diagonalMatrix;
	diagonalMatrix = vector1.asDiagonal();
	cout << " Diagonal matrix is \n\n" << diagonalMatrix;


	// basic matrix operations
	//matrix addition
	MatrixXd A1(2, 2);
	MatrixXd B1(2, 2);

	A1 << 1, 2,
		3, 4;
	B1 << 3, 4,
		5, 6;
	MatrixXd C1 = A1 + B1;
	cout << " \n\n The sum of A1 and B1 is\n\n" << C1 << endl;
	// similarly you can subtract A1 and B1

	//matrix multiplication
	MatrixXd D1 = A1 * B1;
	cout << " \n\n The matrix product of A1 and B1 is\n\n" << D1 << endl;

	//multiplication by a scalar
	int s1 = 2;
	MatrixXd F1;
	F1 = s1 * A1;
	cout << " \n\n The matrix product of the scalar 2 and the matrix A1 is\n\n" << F1 << endl;

	//matrix transpose
	MatrixXd At;
	MatrixXd R1;
	// we can obain a transpose of A1 as follows
	At = A1.transpose();
	cout << "\n\n Original matrix A1\n\n" << A1;
	cout << "\n\n Its transpose\n\n " << At;

	// we can use a transpose operator in expressions
	R1 = A1.transpose() + B1;
	cout << "\n\n Matrix R1=A1^{T}+B1 is\n\n" << R1;

	// here we should be careful, the operation .transpose() might lead to unexpected results in this scenarios
	//	A1 = A1.transpose();
	// cout << " \n\n This should be a transpose of the matrix A1\n\n" << A1 << endl;

	// the correct and safe way to do the matrix transpose is the following
	A1.transposeInPlace();
	cout << " \n\n This should be a transpose of the matrix A1\n\n" << A1 << endl;
	//restore A1 matrix to its original state
	A1.transposeInPlace();
	// matrix inverse
	MatrixXd G1;
	G1 = A1.inverse();
	cout << "\n\n The inverse of the matrix A1 is\n\n" << G1;
	cout << "\n\n Double check A1^{-1}*A1=\n\n" << G1 * A1;
	*/

	system("PAUSE");
	return 0;
}
