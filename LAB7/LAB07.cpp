// LAB07.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
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

using namespace std;

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

int* signal(string tab, int N, float fs, float Ts, float Tb)
{

	ofstream saveINF("informacyjny.txt");
	float *t = new float[N];
	int* inf = new int[N];
	int n = 0;
	float TMP_TB = 0;

	for (int k = 0; k < N; k++)
	{
		t[k] = k / fs;
		TMP_TB = TMP_TB + Ts;
		saveINF << t[k] << " ";
		if (TMP_TB >= Tb)
		{
			n++;
			TMP_TB = 0;
		}
		if (tab[n] == '1')
		{
			inf[k] = 1;
		}
		else
		{
			inf[k] = 0;
		}
		saveINF << inf[k] << endl;
	}
	
	saveINF.close();
	return inf;
}

float * ASK(int * inf, int N, float A1, float A2, float f, float fs)
{
	float *t = new float[N];
	float * zA = new float[N];
	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		if (inf[i] == 0)
		{
			zA[i] = A1 * sin(2 * M_PI * f * t[i]);
		}
		else
		{
			zA[i] = A2 * sin(2 * M_PI * f * t[i]);
		}
	}
	ofstream saveASK("ASK.txt");
	for (int i = 0; i < N; i++)
	{
		saveASK << t[i] << " ";
		saveASK << zA[i] << endl;
	}
	saveASK.close();
	return zA;
}

float * PSK(int * inf, int N, float f, float fs)
{
	float *t = new float[N];
	float * Zp = new float[N];
	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		if (inf[i] == 0)
		{
			Zp[i] = sin(2 * M_PI * f * t[i]);
		}
		else
		{
			Zp[i] = sin(2 * M_PI * f * t[i] + M_PI);
		}
	}
	ofstream savePSK("PSK.txt");
	for (int i = 0; i < N; i++)
	{
		savePSK << t[i] << " ";
		savePSK << Zp[i] << endl;
	}
	savePSK.close();
	return Zp;
}

float * FSK(int * inf, int N, float fn1, float fn2, float fs)
{
	float *t = new float[N];
	float * zF = new float[N];
	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		if (inf[i] == 0)
		{
			zF[i] = sin(2 * M_PI * fn1 * t[i]);
		}
		else
		{
			zF[i] = sin(2 * M_PI * fn2 * t[i]);
		}
	}
	ofstream saveFSK("FSK.txt");
	for (int i = 0; i < N; i++)
	{
		saveFSK << t[i] << " ";
		saveFSK << zF[i] << endl;
	}
	saveFSK.close();
	return zF;
}


int main()
{
	string str = S2BS("AB");
	cout << "AB" << endl;
	cout << str << endl;

	cout << "dl str: ";
	int B = 10; //str.length();
	cout << B << endl;

	float Tb = 1.0/7.0;
	float Tc = B * Tb;
	float fs = 100000;
	float Ts = 1 / fs;
	int N = ceil(Tc / Ts);

	int* inf = signal(str, N, fs, Ts, Tb);

	float A1 = 0; // lepiej zeby nie byla 0; lepiej zmienic na cos niezerowego
	float A2 = 1;

	/*
	float fn = 7;
	float fn1 = 14;
	float fn2 = 7;
	*/

	
	int W = 2; // liczba calkowita

	float fn = W * pow(Tb, -1);
	float fn1 = (W + 1) / Tb;
	float fn2 = (W + 2) / Tb;
	

	
	//ASK
	float * ask = ASK(inf, N, A1, A2, fn, fs);
	//PSK
	float * psk = PSK(inf, N, fn, fs);
	//FSK
	float * fsk = FSK(inf, N, fn1, fn2, fs);

	
	system("PAUSE");
	return 0;
}