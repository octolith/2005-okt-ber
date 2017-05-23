// 2005 okt�ber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

// kiveszi a felesleges karaktereket, a szoveget a vegeig, de legfeljebb 255 karakterig vizsgalja
string atalakit(string eredeti) {
	string atalakitott;
	int meret = 0;
	for (int i = 0; i < eredeti.length() && i < 255; i++) {
		// ha az adott karakter kis- vagy nagybet�, akkor "megtartom", hozz�f�z�m az �jonnan l�trehozott stringhez
		if (eredeti[i] >= 'a' && eredeti[i] <= 'z' || eredeti[i] >= 'A' && eredeti[i] <= 'Z') {
			atalakitott += eredeti[i];
		}
	}
	return atalakitott;
}

// nagybetusiti a kapott szoveget
string nagybetusit(string eredeti) {
	string nagybetusitett;
	for (int i = 0; i < eredeti.length(); i++) {
		nagybetusitett += toupper(eredeti[i]);
	}
	return nagybetusitett;
}

// egymas utan fuzi a kulcsszot annyiszor, hogy olyan hosszu legyen, mint a nyilt szoveg
string osszefuz(string kulcsszo, string szoveg) {
	string kulcsszoveg;
	for (int i = 0; i < szoveg.length(); i++) {
		// a kulcsszo valahany karakter hosszu, ezek ismetlodnek egym�s ut�n
		// marad�kk�pz�ssel veszem a megfelel� karaktert
		kulcsszoveg += kulcsszo[i % kulcsszo.length()];
	}
	return kulcsszoveg;
}

int main()
{
	cout << endl;
	cout << "1. feladat" << endl;
	cout << "Kerem a nyilt szoveget! (maximum 255 karakter hosszu, nem ures, ekezetek nelkuli szoveg)" << endl;
	string szoveg;
	getline(cin, szoveg);

	cout << endl;
	cout << "2. feladat" << endl;
	// �kezetes karakterekkel nem foglalkozunk
	// a szoveg �j �rt�ke legyen annak nagybet�s�tett, �talak�tott (felesleges karakterekt�l mentes) v�ltozata
	szoveg = nagybetusit(atalakit(szoveg));

	cout << endl;
	cout << "3. feladat" << endl;
	cout << szoveg << endl;

	cout << endl;
	cout << "4. feladat" << endl;
	string kulcsszo;
	cout << "Kerem a kulcsszot! (maximum 5 karakteres, nem ures, ekezetek nelkuli szo)" << endl;
	cin >> kulcsszo;
	kulcsszo = nagybetusit(kulcsszo);

	cout << endl;
	cout << "5. feladat" << endl;
	string kulcsszoveg = osszefuz(kulcsszo, szoveg);
	cout << kulcsszoveg << endl;

	cout << endl;
	cout << "6. feladat" << endl;
	// 2D-s karaktert�mbben t�rolom a k�dt�bl�t
	char kodtabla[26][26];
	ifstream fajl_be;
	fajl_be.open("Vtabla.dat");
	if (fajl_be.is_open()) {
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				fajl_be >> kodtabla[i][j];
				//cout << kodtabla[i][j];
			}
		}
		fajl_be.close();

		string kodolt;
		for (int i = 0; i < szoveg.length(); i++) {
			// kihaszn�lom, hogy a karakterek sz�mk�nt vannak t�rolva
			// 'A' lesz a 0 index, 'B' az 1 stb.
			// �gy ha az adott karakterb�l kivonom 'A' �rt�k�t, megkapom az indexet
			// ('A'-'A' = 0, 'B'-'A' = 1, 'C'-'A' = 2 stb.)
			kodolt += kodtabla[szoveg[i] - 'A'][kulcsszoveg[i] - 'A'];
		}

		cout << endl;
		cout << "7. feladat" << endl;
		cout << kodolt << endl;
		ofstream fajl_ki;
		fajl_ki.open("kodolt.dat");
		if (fajl_ki.is_open()) {
			fajl_ki << kodolt;
			fajl_ki.close();
		}
		else {
			cout << "Nem sikerult kiirni a kodolt szoveget." << endl;
		}
	}
	else {
		cout << "Nem sikerult beolvasni a kodtablat." << endl;
	}

	cout << endl << endl;
	system("pause");
	return 0;
}