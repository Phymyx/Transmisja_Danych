// LAB08.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
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


void DFT(float *tablica, string nazwa, int N, float fs)
{
	fstream zad;

	float *tablica_r = new float[N];
	float *tablica_u = new float[N];

	float *tablica_mk = new float[N];
	float *tablica_mk1 = new float[N];
	float *tablica_fk = new float[N];

	for (int k = 0; k <= N - 1; k++)
	{
		tablica_r[k] = 0;
		tablica_u[k] = 0;
		for (int n = 0; n <= N - 1; n++)
		{
			tablica_r[k] += tablica[n] * cos(-(2 * (M_PI * k * n) / N));
			tablica_u[k] += tablica[n] * sin(-(2 * (M_PI * k * n) / N));
		}
	}

	for (int k = 0; k <= N - 1; k++)
	{
		tablica_mk[k] = sqrt(pow(tablica_r[k], 2) + pow(tablica_u[k], 2));
		//tablica_mk[k] = tablica_mk[k] * 2 / N;
	}

	for (int k = 0; k <= N - 1; k++)
	{
		tablica_mk1[k] = 10 * log10(tablica_mk[k]);
		tablica_fk[k] = k * (fs / N);
	}


	zad.open(nazwa, ios::out);
	if (zad.good() == true)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			zad << tablica_fk[i] << " ";
			zad << tablica_mk1[i] << endl;
		}
		zad.close();
	}

}

void minmax(float* band, int n, string nazwa)
{
	float max = band[0];
	float min = band[0];

	for (int i = 1; i < n; i++)
	{
		if (band[i] < min)
		{
			min = band[i];
		}
		if (band[i] > max)
		{
			max = band[i];
		}
	}
	float szerokosc = max - min;
	cout << nazwa << szerokosc << endl;
}


int main()
{
	string str = S2BS("AB");
	cout << "AB" << endl;
	cout << str << endl;

	cout << "dl str: ";
	int B = str.length();
	cout << B << endl;

	float Tb = 1.0 / 7.0;
	float Tc = B * Tb;
	float fs = 10000;//10k
	float Ts = 1 / fs;
	int N = ceil(Tc / Ts);

	int* inf = signal(str, N, fs, Ts, Tb);

	float A1 = 0.5; // lepiej zeby nie byla 0; lepiej zmienic na cos niezerowego
	float A2 = 1;

	/*
	float fn = 7;
	float fn1 = 14;
	float fn2 = 7;
	*/

	/*
	fs = 2*fn
	*/


	int W = 100; // liczba calkowita zwiekszyc na 100 , 1000 moze 2000 moze 3000 a było 2

	float fn = W * pow(Tb, -1);
	float fn1 = (W + 1) / Tb; //  707
	float fn2 = (W + 2) / Tb; //  714


	cout << "wykonuje ASK" << endl;
	//ASK
	float * ask = ASK(inf, N, A1, A2, fn, fs);
	cout << "wykonuje PSK" << endl;
	//PSK
	float * psk = PSK(inf, N, fn, fs);
	cout << "wykonuje FSK" << endl;
	//FSK
	float * fsk = FSK(inf, N, fn1, fn2, fs);


	//DFT
	cout << "DFT_ASK" << endl;
	DFT(ask, "wykonuje DFT_ASK.txt", N, fs);
	cout << "DFT_PSK" << endl;
	DFT(psk, "wykonuje DFT_PSK.txt", N, fs);
	cout << "DFT_FSK" << endl;
	DFT(fsk, "wykonuje DFT_FSK.txt", N, fs);

	//minmax
	minmax(ask, N, "szerokosc ASK: "); //2
	minmax(psk, N, "szerokosc PSK: "); //2
	minmax(fsk, N, "szerokosc FSK: "); //2


	system("PAUSE");
	return 0;
}