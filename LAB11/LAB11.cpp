// LAB11.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
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

using namespace std;

const int liczba_bitow_pakiet = 4;

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

int* Hamming(int* in)
{
	int* b = new int[4];
	int* X = new int[7];

	cout << "pierwsze 4 bity: ";

	for (int i = 0; i < liczba_bitow_pakiet; i++)
	{
		b[i] = in[i];
		cout << b[i];
	}

	cout << endl;

	X[0] = ((b[0] + b[1] + b[3]) % 2);
	X[1] = ((b[0] + b[2] + b[3]) % 2);
	X[2] = b[0];
	X[3] = ((b[1] + b[2] + b[3]) % 2);
	X[4] = b[1];
	X[5] = b[2];
	X[6] = b[3];

	cout << "Hamming: ";

	for (int j = 0; j < 7; j++)
	{
		cout << X[j];
	}

	cout << endl;


	return X;
}

int* DekHamming(int* in)
{
	int* bp = new int[4];

	int x1p = ((in[2] + in[4] + in[6]) % 2);
	int x2p = ((in[2] + in[5] + in[6]) % 2);
	int x4p = ((in[4] + in[5] + in[6]) % 2);

	int x1d = ((in[0] + x1p) % 2);
	int x2d = ((in[1] + x2p) % 2);
	int x4d = ((in[3] + x4p) % 2);

	int S = x1d + x2d * 2 + x4d * 4;

	cout << "S: " << S << endl;

	if (S == 0)
	{
		bp[0] = in[2];
		bp[1] = in[4];
		bp[2] = in[5];
		bp[3] = in[6];

		cout << "b': ";

		for (int i = 0; i < liczba_bitow_pakiet; i++)
		{
			cout << bp[i];
		}

		cout << endl;
	}
	else
	{
		cout << "Wystapil blad na pozycji " << S << endl;
		in[S - 1] = !in[S - 1];
		cout << "Hamming po naprawie bitu: ";

		for (int j = 0; j < 7; j++)
		{
			cout << in[j];
		}
		cout << endl;

		bp[0] = in[2];
		bp[1] = in[4];
		bp[2] = in[5];
		bp[3] = in[6];

		cout << "b': ";

		for (int i = 0; i < liczba_bitow_pakiet; i++)
		{
			cout << bp[i];
		}

		cout << endl;
	}

	return bp;
}

void Negacja(int* &in, int index)
{
	in[index - 1] = !in[index - 1];
}

int main()
{
	string str = S2BS("h");
	cout << "h" << endl;
	cout << str << endl;

	cout << "dl str: ";
	int B = str.length();
	cout << B << endl;


	int * bity = s2ch(str, B);

	int * Hamming1 = Hamming(bity);

	int * DekHamming1 = DekHamming(Hamming1);

	int index = 5;
	cout << "Negacja " << index << " bitu" << endl;
	Negacja(Hamming1, index);

	cout << "Hamming po negacji: ";

	for (int j = 0; j < 7; j++)
	{
		cout << Hamming1[j];
	}
	cout << endl;

	int * DekHamming2 = DekHamming(Hamming1);

	system("PAUSE");
	return 0;
}
