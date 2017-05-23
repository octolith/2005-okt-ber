// 2006 október.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Dal {
	int radio;
	int hossz;
	string azonosito;
};

int main()
{
	cout << endl;
	cout << "1. feladat" << endl;
	Dal adas[1000];
	int db;
	ifstream fajl_be("musor.txt");
	if (fajl_be.is_open()) {
		fajl_be >> db;
		for (int i = 0; i < db; i++) {
			int perc, mp;
			fajl_be >> adas[i].radio >> perc >> mp;
			adas[i].hossz = perc * 60 + mp;
			string sorvege;
			getline(fajl_be, sorvege);
			getline(fajl_be, adas[i].azonosito);
		}
	}
	else {
		db = 10;
		//TODO
	}


	cout << endl;
	cout << "2. feladat" << endl;

	int csatornak[4] = { 0 };
	for (int i = 0; i < db; i++) {
		csatornak[adas[i].radio]++;
	}
	for (int i = 1; i <= 3; i++) {
		cout << i << ". csatorna: " << csatornak[i] << " szam" << endl;
	}


	cout << endl;
	cout << "3. feladat" << endl;

	bool elso = true;
	int ido = 0;
	int elso_kezdete;
	int utolso_vege;
	for (int i = 0; i < db; i++) {
		if (adas[i].radio == 1) {
			if (adas[i].azonosito.find("Eric Clapton") == 0) {
				if (elso) {
					elso_kezdete = ido;
					ido += adas[i].hossz;
					utolso_vege = ido;
				}
				else {
					ido += adas[i].hossz;
					utolso_vege = ido;
				}
			}
			else {
				ido += adas[i].hossz;
			}
		}

		
	}

	return 0;
}

