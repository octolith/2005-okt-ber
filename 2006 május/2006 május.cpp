// 2006 május.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Aminosav {
	string rovidites;
	char betujel;
	int c;
	int h;
	int o;
	int n;
	int s;
};

// állapotgép a 6. feladathoz
enum Allapot {
	alap,
	R_volt
};

// 2. feladat
int molekulatomeg(Aminosav a) {
	return a.c * 12 + a.h * 1 + a.o * 16 + a.n * 14 + a.s * 32;
}

int main() {
	cout << endl;
	cout << "1. feladat" << endl;
	int amino_db = 0;
	Aminosav aminosavak[20];
	ifstream fajl_be("aminosav.txt");
	if (fajl_be.is_open()) {
		amino_db = 20;
		for (int i = 0; i < amino_db; i++) {
			fajl_be >> aminosavak[i].rovidites >> aminosavak[i].betujel >> aminosavak[i].c >> aminosavak[i].h >> aminosavak[i].o >> aminosavak[i].n >> aminosavak[i].s;
			//cout << aminosavak[i].rovidites << " " << aminosavak[i].betujel << " " << aminosavak[i].c << " " << aminosavak[i].h << " " << aminosavak[i].o << " " << aminosavak[i].n << " " << aminosavak[i].s << endl;
		}
		fajl_be.close();
	}
	else {
		amino_db = 5;

		aminosavak[0].rovidites = "Gly";
		aminosavak[1].rovidites = "Ala";
		aminosavak[2].rovidites = "Arg";
		aminosavak[3].rovidites = "Phe";
		aminosavak[4].rovidites = "Cys";

		aminosavak[0].betujel = 'G';
		aminosavak[1].betujel = 'A';
		aminosavak[2].betujel = 'R';
		aminosavak[3].betujel = 'F';
		aminosavak[4].betujel = 'C';

		aminosavak[0].c = 1;
		aminosavak[1].c = 3;
		aminosavak[2].c = 6;
		aminosavak[3].c = 9;
		aminosavak[4].c = 3;

		aminosavak[0].h = 5;
		aminosavak[1].h = 7;
		aminosavak[2].h = 14;
		aminosavak[3].h = 11;
		aminosavak[4].h = 7;

		aminosavak[0].o = 2;
		aminosavak[1].o = 2;
		aminosavak[2].o = 2;
		aminosavak[3].o = 2;
		aminosavak[4].o = 2;

		aminosavak[0].n = 1;
		aminosavak[1].n = 1;
		aminosavak[2].n = 4;
		aminosavak[3].n = 1;
		aminosavak[4].n = 1;

		aminosavak[0].s = 0;
		aminosavak[1].s = 0;
		aminosavak[2].s = 0;
		aminosavak[3].s = 0;
		aminosavak[4].s = 1;
		/*
		for (int i = 0; i < amino_db; i++) {
			cout << aminosavak[i].rovidites << " " << aminosavak[i].betujel << " " << aminosavak[i].c << " " << aminosavak[i].h << " " << aminosavak[i].o << " " << aminosavak[i].n << " " << aminosavak[i].s << endl;
		}
		*/
	}

	// 3. feladat
	// rendezés molakulatömeg szerint, buborékrendezéses módszerrel
	for (int i = amino_db - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (molekulatomeg(aminosavak[j]) > molekulatomeg(aminosavak[j + 1])) {
				Aminosav temp = aminosavak[j];
				aminosavak[j] = aminosavak[j + 1];
				aminosavak[j + 1] = temp;
			}
		}
	}


	// 4. feladat
	char bsa[1000];
	int bsa_db = 0;
	int bsa_c = 0;
	int bsa_h = 0;
	int bsa_o = 0;
	int bsa_n = 0;
	int bsa_s = 0;

	fajl_be.open("bsa.txt");
	if (fajl_be.is_open()) {
		while (fajl_be >> bsa[bsa_db]) {
			bsa_db++;
		}
		fajl_be.close();
	}
	else {
		int bsa_db = 50;
		for (int i = 0; i < bsa_db; i++) {
			switch (i % 5) {
			case 0:
				bsa[i] = 'G';
				break;
			case 1:
				bsa[i] = 'A';
				break;
			case 2:
				bsa[i] = 'R';
				break;
			case 3:
				bsa[i] = 'F';
				break;
			case 4:
				bsa[i] = 'C';
				break;
			}
		}
	}

	for (int i = 0; i < bsa_db; i++) {
		for (int j = 0; j < amino_db; j++) {
			if (bsa[i] == aminosavak[j].betujel) {
				bsa_c += aminosavak[j].c;
				bsa_h += aminosavak[j].h - 2;
				bsa_o += aminosavak[j].o - 1;
				bsa_n += aminosavak[j].n;
				bsa_s += aminosavak[j].s;
				break;
			}
		}
		//a legelso aminosavnal nem kell levonni, ugyhogy visszaadom a hianyzo atomokat
		bsa_h += 2;
		bsa_o += 1;
	}

	// 5. feladat
	int aktualis_hossz = 0;
	int max_hossz = 0;
	int max_vegenek_indexe = 0;
	for (int i = 0; i < bsa_db; i++) {
		// valami betu -> lanc hossza no
		aktualis_hossz++;

		// szakit?
		if (bsa[i] == 'Y' || bsa[i] == 'W' || bsa[i] == 'F' || i == bsa_db - 1) {
			//cout << " szakit ";
			if (aktualis_hossz > max_hossz) {
				//cout << " max ";
				max_hossz = aktualis_hossz;
				// lánc végének indexe, az elejét úgy kapom meg, hogy max_vegenek_indexe-max_hossz
				max_vegenek_indexe = i;
			}
			//szakítás volt, tehát az aktuális hosszt nullázom
			aktualis_hossz = 0;
		}
		//cout << endl;
	}


	// 6. feladat
	Allapot all = alap;
	int i = 0;
	// ezzel a logikai valtozoval allitom meg a ciklust az elso hasitasnal
	bool volt_hasitas = false;
	int cisztein_db = 0;
	while (i < bsa_db && !volt_hasitas) {
		// allapotgeppel vizsgalom, hogy tortenik-e szakitas
		switch (all) {
		case alap:
			switch (bsa[i]) {
			case 'R':
				all = R_volt;
				break;
			case 'C':
				all = alap;
				cisztein_db++;
				break;
			default:
				all = alap;
				break;
			}
			break;
		case R_volt:
			switch (bsa[i]) {
			case 'R':
				all = R_volt;
				break;
			case 'A':
			case 'V':
				all = alap;
				volt_hasitas = true;
				break;
			case 'C':
				all = alap;
				cisztein_db++;
				break;
			default:
				all = alap;
				break;
			}
			break;
		default:
			break;
		}
		i++;
	}

	

	// kiiras a standard kimenetre
	cout << endl;
	cout << "3. feladat" << endl;
	for (int i = 0; i < amino_db; i++) {
		cout << aminosavak[i].rovidites << " " << molekulatomeg(aminosavak[i]) << endl;
	}

	cout << endl;
	cout << "4. feladat" << endl;
	cout << "C " << bsa_c << " H " << bsa_h << " O " << bsa_o << " N " << bsa_n << " S " << bsa_s << endl;

	cout << endl;
	cout << "5. feladat" << endl;
	cout << "Kezdet helye: " << max_vegenek_indexe + 2 - max_hossz << " " << "Vege: " << max_vegenek_indexe + 1 << endl;
	cout << "Hossza: " << max_hossz << endl;

	cout << endl;
	cout << "6. feladat" << endl;
	cout << cisztein_db << " db Cisztein talalhato az elso feherjelancban." << endl;


	//kiiras fajlba
	ofstream fajl_ki("eredmeny.txt");
	if(fajl_ki.is_open()) {
		fajl_ki << "3. feladat" << endl;
		for (int i = 0; i < amino_db; i++) {
			fajl_ki << aminosavak[i].rovidites << " " << molekulatomeg(aminosavak[i]) << endl;
		}

		fajl_ki << endl;
		fajl_ki << "4. feladat" << endl;
		fajl_ki << "C " << bsa_c << "H " << bsa_h << " O " << bsa_o << " N " << bsa_n << " S " << bsa_s << endl;

		fajl_ki << endl;
		fajl_ki << "5. feladat" << endl;
		fajl_ki << "Kezdet helye: " << max_vegenek_indexe + 2 - max_hossz << " " << "Vege: " << max_vegenek_indexe + 1 << endl;
		fajl_ki << "Hossza: " << max_hossz << endl;

		fajl_ki << endl;
		fajl_ki << "6. feladat" << endl;
		fajl_ki << cisztein_db << " db Cisztein talalhato az elso feherjelancban." << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}

