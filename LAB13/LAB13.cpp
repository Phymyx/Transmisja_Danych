// LAB13.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
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
#include <time.h>

using namespace std;

const int liczba_bitow_pakiet = 4;

string oddzielacz = "\n =============================== \n";


string S2BS(string in)
{
	cout << in << endl;

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

int* Hamming(int* in, int B)
{
	int* b = new int[4];
	int wielkosc_tab_X = (B / 4) * 7;
	cout << "wielkosc tablicy X: " << wielkosc_tab_X << endl;
	
	int* X = new int[wielkosc_tab_X];//pakiety po 7

	int k = 0;

	for (int j = 0; j < B; j = j + 4)
	{

		cout << "pakiety 4 bitowe: ";

		for (int i = 0; i < liczba_bitow_pakiet; i++)
		{
			b[i] = in[i+j];
			cout << b[i];
		}

		cout << endl;

		X[0 + k] = ((b[0] + b[1] + b[3]) % 2);
		X[1 + k] = ((b[0] + b[2] + b[3]) % 2);
		X[2 + k] = b[0];
		X[3 + k] = ((b[1] + b[2] + b[3]) % 2);
		X[4 + k] = b[1];
		X[5 + k] = b[2];
		X[6 + k] = b[3];

		k = k + 7;
	}

	cout << "Hamming: ";

	for (int j = 0; j < wielkosc_tab_X; j++)
	{
		cout << X[j];
	}

	cout << endl;

	return X;
}

int* DekHamming(int* in, int B)
{
	int wielkosc_tab_X = (B / 4) * 7;
	int wielkosc_bp = wielkosc_tab_X / 7;

	//cout << "wielkosc_bp: " << wielkosc_bp << endl;//14

	int* bp = new int[B];//14

	//int wielkosc_tab_X = (B / 4) * 7;

	//cout << "wielkosc_tab_X: " << wielkosc_tab_X << endl;//98

	int k = 0;
	int z = 1;

	
	for (int j = 0; j < wielkosc_tab_X; j = j + 7)
	{
		int x1p = ((in[2 + j] + in[4 + j] + in[6 + j]) % 2);
		int x2p = ((in[2 + j] + in[5 + j] + in[6 + j]) % 2);
		int x4p = ((in[4 + j] + in[5 + j] + in[6 + j]) % 2);

		int x1d = ((in[0 + j] + x1p) % 2);
		int x2d = ((in[1 + j] + x2p) % 2);
		int x4d = ((in[3 + j] + x4p) % 2);

		int S = x1d + x2d * 2 + x4d * 4;

		//cout << "S dla pakietu " << z << " wynosi: " << S << endl;

		if (S == 0)
		{
			bp[0 + k] = in[2 + j];
			bp[1 + k] = in[4 + j];
			bp[2 + k] = in[5 + j];
			bp[3 + k] = in[6 + j];
		}
		else
		{
			//cout << "Wystapil blad na pozycji " << S << endl;
			in[S - 1 + j] = !in[S - 1 + j];//było bez j  powinien być dla paczki 6: 2 i 7 bit zmieniony a nie 5
			//cout << "Hamming po naprawie bitu: ";

			for (int j = 0; j < wielkosc_tab_X; j++)
			{
				//cout << in[j];
			}
			cout << endl;

			bp[0 + k] = in[2 + j];
			bp[1 + k] = in[4 + j];
			bp[2 + k] = in[5 + j];
			bp[3 + k] = in[6 + j];
		}
		k = k + 4;
		z++;
	}

	cout << "b': ";

	for (int i = 0; i < B; i++)
	{
		cout << bp[i];
	}

	cout << endl;
	


	/*
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
	*/
	return bp;
	//return 0;
}

int* signal(int* tab, int N, float fs, float Ts, float Tb)
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
		if (tab[n] == 1)
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

	/*
	ofstream saveDEMPSK("xtPSK.txt");
	for (int i = 0; i < N; i++)
	{
		saveDEMPSK << t[i] << " ";
		saveDEMPSK << X[i] << endl;
	}
	saveDEMPSK.close();
	*/
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

	/*
	ofstream saveDEMASK("xtASK.txt");
	for (int i = 0; i < N; i++)
	{
		saveDEMASK << t[i] << " ";
		saveDEMASK << X[i] << endl;
	}
	saveDEMASK.close();
	*/
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
			if (ct[k + licznik] == 1)
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


float* noise(float* signal, int size, string outputFileName, float alpha, float fs, int wybor)
{
	if (wybor == 1)
	{
		fstream file;

		float* szum = new float[size];
		float *t = new float[size];

		file.open(outputFileName, fstream::out | fstream::trunc);

		if (file.good())
		{
			/* Generate a new random seed from system time - do this once in your constructor */
			srand(time(NULL));

			/* Setup constants */
			const static int q = 15;
			const static float c1 = (1 << q) - 1;
			const static float c2 = ((int)(c1 / 3)) + 1;
			const static float c3 = 1.f / c1;

			/* random number in range 0 - 1 not including 1 */
			float random = 0.f;

			/* the white noise */
			float noise = 0.f;

			for (int i = 0; i < size; i++)
			{
				t[i] = i / fs;
				random = ((float)rand() / (float)(RAND_MAX + 1));
				noise = round((2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3);

				//signal[i] = (signal[i] * alpha) + (noise * (1.0 - alpha));
				signal[i] = signal[i] + (noise * alpha);
				file << t[i] << " ";
				file << signal[i] << endl;

				//if (i + 1 < size) file << endl;
			}
		}
		file.close();

		return signal;
	}
	else
	{
		return signal;
	}
}


vector<bool> arr2vec(int* in, int B)
{

	vector<bool> dest;

	//cout << "arr2vec: ";

	for (int i = 0; i < B; i++)
	{
		dest.push_back(in[i]);
		//cout << dest[i];
	}

	//cout << endl;

	return dest;
}


double BERfunction(int* in, int* out, int B, string nazwa, double alfa)
{

	vector<bool> sent = arr2vec(in, B);
	vector<bool> received = arr2vec(out, B);


	if (sent.size() != received.size()) return 0.;

	unsigned short badBitsCounter = 0;

	for (size_t i = 0; i < sent.size(); i++)
	{
		if (sent[i] != received[i]) badBitsCounter++;
	}

	cout << "Ilosc zlych bitow po uzyciu " << nazwa << " przy alfa = " << alfa << " : " << badBitsCounter << endl;

	return (double)((double)badBitsCounter / (double)received.size());

}


void genBER(float* ask, float* fsk, float* psk, int N, float fn, float A, float fs, float Ts, float Tb, float fn1, float fn2, int dl_Hamming, int B, int* bity)
{
	double krok = 0.05;//0.1, 0.05
	int probki = 1 / krok;

	cout << "probki: " << probki << endl;

	float* a = new float[probki];
	double* bertabASK = new double[probki];
	double* bertabPSK = new double[probki];
	double* bertabFSK = new double[probki];

	ofstream savebertabASK("berask.txt");
	ofstream savebertabPSK("berpsk.txt");
	ofstream savebertabFSK("berfsk.txt");

	double alpha = 0.0;
	int wybor = 1;

	for (int i = 0; i <= probki; i++)
	{
		cout << "alfa = " << alpha << endl;
		
		a[i] = alpha;

		float* asknoise = noise(ask, N, "ASKszum.txt", alpha, fs, wybor);

		//float* fsknoise = noise(fsk, N, "FSKszum.txt", alpha, wybor);

		//float* psknoise = noise(psk, N, "PSKszum.txt", alpha, wybor);

		cout << oddzielacz;

		
		cout << "demodulator PSK" << endl;
		//int * demPSK = demodulatorPSK(psknoise, fn, N, A, fs, Ts, Tb);

		cout << "demodulator FSK" << endl;
		//int * demFSK = demodulatorFSK(fsknoise, fn1, fn2, N, A, fs, Ts, Tb);
		
		cout << "demodulator ASK" << endl;
		int * demASK = demodulatorASK(asknoise, fn, N, A, fs, 126, Ts, Tb);
		//126 i moze zmienic na cos wiecej, pokombinowac

		cout << oddzielacz;

		
		cout << "c' PSK: ";
		//int * ct2bPSK = ct2b(demPSK, fs, Tb, 50, dl_Hamming);

		cout << "c' FSK: ";
		//int * ct2bFSK = ct2b(demFSK, fs, Tb, 50, dl_Hamming);
		
		cout << "c' ASK: ";
		int * ct2bASK = ct2b(demASK, fs, Tb, 65, dl_Hamming);//50


		//int * DekHamming1 = DekHamming(ct2bPSK, B);
		//int * DekHamming2 = DekHamming(ct2bFSK, B);
		int * DekHamming3 = DekHamming(ct2bASK, B);

		//double berPSK = BERfunction(bity, DekHamming1, B, "PSK", alpha);
		//double berFSK = BERfunction(bity, DekHamming2, B, "FSK", alpha);
		double berASK = BERfunction(bity, DekHamming3, B, "ASK", alpha);

		bertabASK[i] = berASK;
		//bertabPSK[i] = berPSK;
		//bertabFSK[i] = berFSK;

		savebertabASK << a[i] << " ";
		savebertabASK << bertabASK[i] << endl;

		savebertabPSK << a[i] << " ";
		savebertabPSK << bertabPSK[i] << endl;

		savebertabFSK << a[i] << " ";
		savebertabFSK << bertabFSK[i] << endl;

		alpha = alpha + krok;
	}

	savebertabASK.close();
	savebertabPSK.close();
	savebertabFSK.close();
}

int main()
{
	string str = S2BS("abcdabcd");//50-60
	cout << str << endl;

	cout << "dl str: ";
	int B = str.length();
	cout << B << endl;

	int dl_Hamming = (B / 4) * 7;

	float Tb = 0.01;
	float Tc = dl_Hamming * Tb;//dl_Hamming * Tb
	float fs = 100000;//100k
	float Ts = 1 / fs;
	int N = ceil(Tc / Ts);

	float A = 1;
	float A1 = 0.5;//1
	float A2 = 1;//0.5

	int W = 1; //było 100 liczba calkowita zwiekszyc na 100 , 1000 moze 2000 moze 3000 a było 2

	float fn = W * pow(Tb, -1);
	float fn1 = (W + 1) / Tb;
	float fn2 = (W + 2) / Tb;


	int * bity = s2ch(str, B);

	int * Hamming1 = Hamming(bity, B);

	int* inf = signal(Hamming1, N, fs, Ts, Tb);


	cout << oddzielacz;


	//PSK
	cout << "wykonuje PSK" << endl;
	float * psk = PSK(inf, N, fn, fs);

	//FSK
	cout << "wykonuje FSK" << endl;
	float * fsk = FSK(inf, N, fn1, fn2, fs);

	//ASK
	cout << "wykonuje ASK" << endl;
	float * ask = ASK(inf, N, A1, A2, fn, fs);

	cout << oddzielacz;
	
	cout << endl << "zaszumianie..." << endl;
	
	double alpha = 0.7;// 0.1, 0.4, 0.7
	int wybor = 1;//0-zaszumianie wylaczone, 1 - zaszumianie wlaczone
	//krok
	float* asknoise = noise(ask, N, "ASKszum.txt", alpha, fs, wybor);

	float* fsknoise = noise(fsk, N, "FSKszum.txt", alpha, fs, wybor);

	float* psknoise = noise(psk, N, "PSKszum.txt", alpha, fs, wybor);

	cout << oddzielacz;

	/*
	cout << "demodulator PSK" << endl;
	int * demPSK = demodulatorPSK(psknoise, fn, N, A, fs, Ts, Tb);

	cout << "demodulator FSK" << endl;
	//int * demFSK = demodulatorFSK(fsknoise, fn1, fn2, N, A, fs, Ts, Tb);

	cout << "demodulator ASK" << endl;
	int * demASK = demodulatorASK(asknoise, fn, N, A, fs, 126, Ts, Tb); // bylo 126 ale cos pozmieniam i zobacze


	cout << oddzielacz;

	
	//cout << "c' PSK: ";
	int * ct2bPSK = ct2b(demPSK, fs, Tb, 50, dl_Hamming);

	//cout << "c' FSK: ";
	//int * ct2bFSK = ct2b(demFSK, fs, Tb, 50, dl_Hamming);

	cout << "c' ASK: ";
	int * ct2bASK = ct2b(demASK, fs, Tb, 51, dl_Hamming);//50, 75

	
	int * DekHamming1 = DekHamming(ct2bPSK, B);
	//int * DekHamming2 = DekHamming(ct2bFSK, B);
	int * DekHamming3 = DekHamming(ct2bASK, B);

	BS2S(DekHamming1, B, "z b' PSK: ");
	//BS2S(DekHamming2, B, "z b' FSK: ");
	BS2S(DekHamming3, B, "z b' ASK: ");

	
	BERfunction(bity, DekHamming1, B, "PSK", alpha);
	//BERfunction(bity, DekHamming2, B, "FSK", alpha);
	
	BERfunction(bity, DekHamming3, B, "ASK", alpha);
	
	//vector<bool> arr2vec1 = arr2vec(DekHamming1, B);
	*/

	//genBER(ask, fsk, psk, N, fn, A, fs, Ts, Tb, fn1, fn2, dl_Hamming, B, bity);

	system("PAUSE");
	return 0;
}