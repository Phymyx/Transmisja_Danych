// LAB10.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
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


string BS2S(int* in, int B, string nazwa)
{
	stringstream ss;
	for (int i = 0; i < B; i++)
	{
		if (in[i] != 0)
		{
			ss << "";
		}
		ss << in[i];
	}
	string s = ss.str();
	//cout << "string BS2S: " << s << endl;

	stringstream sstream(s);
	string stri;

	while (sstream.good())
	{
		bitset<7> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		stri += c;
	}

	cout << "string BS2S " << nazwa << ": " << stri << endl;

	return stri;
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

	/*
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
	*/
}

////////////////////////////////////Demodulator//////////////////////////////////////////////

float* sinusoid(float f, int N, float A, float fs)
{
	float *t = new float[N];
	float* sinus = new float[N];
	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		sinus[i] = A * sin(2 * M_PI * f * t[i]);
	}
	return sinus;
}


int* demodulatorASK(float* pasmo, float f, int N, float A, float fs, float h, float Ts, float Tb)
{
	//1:

	float* sinus = sinusoid(f, N, A, fs);
	float* X = new float[N];
	float *t = new float[N];

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		X[i] = pasmo[i] * sinus[i];
	}

	ofstream saveDEMASK("xtASK.txt");
	for (int i = 0; i < N; i++)
	{
		saveDEMASK << t[i] << " ";
		saveDEMASK << X[i] << endl;
	}
	saveDEMASK.close();

	//2,3:



	float* pt = new float[N];
	int* ct = new int[N];

	ofstream saveDemASK_P("ptASK.txt");
	ofstream saveDemASK("ctASK.txt");



	float *t1 = new float[N];
	int n = 0;
	float TMP_TB = 0;


	float calka = 0;

	for (int i = 0; i < N; i++)
	{

		t1[i] = i / fs;
		TMP_TB = TMP_TB + Ts;
		saveDemASK_P << t1[i] << " ";
		saveDemASK << t1[i] << " ";
		if (TMP_TB >= Tb)
		{
			n++;
			TMP_TB = 0;
			calka = 0;
		}
		calka += X[i];

		saveDemASK_P << calka << endl;


		if (calka > h)
		{
			ct[i] = 1;
		}
		else
		{
			ct[i] = 0;
		}
		saveDemASK << ct[i] << endl;
	}
	saveDemASK.close();
	saveDemASK_P.close();

	return ct;

}


int* demodulatorPSK(float* pasmo, float f, int N, float A, float fs, float Ts, float Tb)
{
	//1:

	float* sinus = sinusoid(f, N, A, fs);
	float* X = new float[N];
	float *t = new float[N];

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		X[i] = pasmo[i] * sinus[i];
	}

	ofstream saveDEMPSK("xtPSK.txt");
	for (int i = 0; i < N; i++)
	{
		saveDEMPSK << t[i] << " ";
		saveDEMPSK << X[i] << endl;
	}
	saveDEMPSK.close();

	//2,3:



	float* pt = new float[N];
	int* ct = new int[N];

	ofstream saveDemPSK_P("ptPSK.txt");
	ofstream saveDemPSK("ctPSK.txt");



	float *t1 = new float[N];
	int n = 0;
	float TMP_TB = 0;


	float calka = 0;

	for (int i = 0; i < N; i++)
	{

		t1[i] = i / fs;
		TMP_TB = TMP_TB + Ts;
		saveDemPSK_P << t1[i] << " ";
		saveDemPSK << t1[i] << " ";
		if (TMP_TB >= Tb)
		{
			n++;
			TMP_TB = 0;
			calka = 0;
		}
		calka += X[i];

		saveDemPSK_P << calka << endl;


		if (calka < 0)
		{
			ct[i] = 1;
		}
		else
		{
			ct[i] = 0;
		}
		saveDemPSK << ct[i] << endl;
	}
	saveDemPSK.close();
	saveDemPSK_P.close();

	return ct;

}


int* demodulatorFSK(float* pasmo, float f1, float f2, int N, float A, float fs, float Ts, float Tb)
{
	//1:

	float* sinus1 = sinusoid(f1, N, A, fs);
	float* sinus2 = sinusoid(f2, N, A, fs);
	float* X1 = new float[N];
	float* X2 = new float[N];
	float *t = new float[N];

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		X1[i] = pasmo[i] * sinus1[i];
	}

	ofstream savex1t("x1tFSK.txt");
	for (int i = 0; i < N; i++)
	{
		savex1t << t[i] << " ";
		savex1t << X1[i] << endl;
	}
	savex1t.close();

	for (int i = 0; i < N; i++)
	{
		t[i] = i / fs;
		X2[i] = pasmo[i] * sinus2[i];
	}

	ofstream savex2t("x2tFSK.txt");
	for (int i = 0; i < N; i++)
	{
		savex2t << t[i] << " ";
		savex2t << X2[i] << endl;
	}
	savex2t.close();

	//2,3:



	float* p1t = new float[N];
	float* p2t = new float[N];
	int* ct = new int[N];

	ofstream savep1t("p1tFSK.txt");
	ofstream savep2t("p2tFSK.txt");
	ofstream savept("ptFSK.txt");
	ofstream saveDemFSK("ctFSK.txt");



	float *t1 = new float[N];
	int n = 0;
	float TMP_TB = 0;

	float calka = 0;
	float calka1 = 0;
	float calka2 = 0;

	for (int i = 0; i < N; i++)
	{

		t1[i] = i / fs;
		TMP_TB = TMP_TB + Ts;
		savep1t << t1[i] << " ";
		savep2t << t1[i] << " ";
		savept << t1[i] << " ";
		saveDemFSK << t1[i] << " ";
		if (TMP_TB >= Tb)
		{
			n++;
			TMP_TB = TMP_TB - Tb;
			calka1 = 0;
			calka2 = 0;
			calka = 0;
		}
		calka1 += X1[i];
		calka2 += X2[i];
		calka += calka2 - calka1;

		savep1t << calka1 << endl;
		savep2t << calka2 << endl;
		savept << calka << endl;


		if (calka > 0)
		{
			ct[i] = 1;
		}
		else
		{
			ct[i] = 0;
		}
		saveDemFSK << ct[i] << endl;
	}
	saveDemFSK.close();
	savep1t.close();
	savep2t.close();
	savept.close();

	return ct;

}

int* ct2b(int* ct, float fs, float Tb, float procent, int B)
{
	int* binary = new int[B];

	float suma1 = 0;
	float suma0 = 0;

	int probki_na_bit = Tb * fs;

	int licznik = 0;

	float procencik = procent / 100;

	float zmienna = probki_na_bit * procencik;

	for (int i = 0; i < B; i++)
	{
		suma1 = 0;
		suma0 = 0;
		for (int k = 0; k < probki_na_bit; k++)
		{
			if (ct[k+licznik] == 1)
			{
				suma1++;
			}
			else
			{
				suma0++;
			}
		}
		//cout << "suma1: " << suma1 << endl;
		//cout << "suma0: " << suma0 << endl;

		//(suma1 > suma0)

		if (suma1 > zmienna)
		{
			binary[i] = 1;
		}
		else
		{
			binary[i] = 0;
		}
		cout << binary[i];
		licznik = licznik + probki_na_bit;
	}
	
	cout << endl;

	return binary;

}


int main()
{
	string str = S2BS("AKZ");
	cout << "AKZ" << endl;
	cout << str << endl;

	cout << "dl str: ";
	int B = str.length();
	cout << B << endl;

	//float Tb = 1.0 / 7.0;
	float Tb = 0.01;
	float Tc = B * Tb;
	float fs = 100000;//100k
	float Ts = 1 / fs;
	int N = ceil(Tc / Ts);

	int* inf = signal(str, N, fs, Ts, Tb);

	float A1 = 0; //0.5 lepiej zeby nie byla 0; lepiej zmienic na cos niezerowego
	float A2 = 1;
	float A = 1;

	/*
	float fn = 7;
	float fn1 = 14;
	float fn2 = 7;
	*/

	/*
	fs = 2*fn
	*/


	int W = 1; //było 100 liczba calkowita zwiekszyc na 100 , 1000 moze 2000 moze 3000 a było 2

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
	/*
	cout << "DFT_ASK" << endl;
	DFT(ask, "wykonuje DFT_ASK.txt", N, fs);
	cout << "DFT_PSK" << endl;
	DFT(psk, "wykonuje DFT_PSK.txt", N, fs);
	cout << "DFT_FSK" << endl;
	DFT(fsk, "wykonuje DFT_FSK.txt", N, fs);
	*/

	//DEMODULATOR
	cout << "demodulator ASK" << endl;
	int * demASK = demodulatorASK(ask, fn, N, A, fs, 0, Ts, Tb);

	cout << "demodulator PSK" << endl;
	int * demPSK = demodulatorPSK(psk, fn, N, A, fs, Ts, Tb);

	cout << "demodulator FSK" << endl;
	int * demFSK = demodulatorFSK(fsk, fn1, fn2, N, A, fs, Ts, Tb);

	cout << "ct2b ASK: " << endl;
	int * ct2bASK = ct2b(demASK, fs, Tb, 50, B);

	cout << "ct2b PSK: " << endl;
	int * ct2bPSK = ct2b(demPSK, fs, Tb, 50, B);

	cout << "ct2b FSK: " << endl;
	int * ct2bFSK = ct2b(demFSK, fs, Tb, 50, B);

	BS2S(ct2bASK, B, "ASK");
	BS2S(ct2bPSK, B, "PSK");
	BS2S(ct2bFSK, B, "FSK");


	system("PAUSE");
	return 0;
}