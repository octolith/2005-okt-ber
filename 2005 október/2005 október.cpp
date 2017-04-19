// 2005 október.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// kiveszi a felesleges karaktereket
string atalakit(string eredeti) {
	stringstream atalakitott;
	int meret = 0;
	for (int i = 0; i < eredeti.length() && meret <= 255; i++) {
		if (eredeti[i] >= 'a' && eredeti[i] <= 'z' || eredeti[i] >= 'A' && eredeti[i] <= 'Z') {
			atalakitott << eredeti[i];
			meret++;
		}
	}
	return atalakitott.str();
}

// nagybetusiti a kapott szoveget
string nagybetusit(string eredeti) {
	for (int i = 0; i < eredeti.length(); i++) {
		eredeti[i] = toupper(eredeti[i]);
	}
	return eredeti;
}

// egymas utan fuzi az elso stringet annyiszor, hogy olyan hosszu legyen, mint a masodik string
string osszefuz(string kulcsszo, string szoveg) {
	stringstream kulcsszoveg;
	for (int i = 0; i < szoveg.length(); i++) {
		kulcsszoveg << kulcsszo[i % kulcsszo.length()];
	}
	return kulcsszoveg.str();
}

int main()
{
	// 1. feladat
	cout << "Kerem a nyilt szoveget! (maximum 255 karakter hosszu, ekezetek nelkuli szoveg)" << endl;
	string szoveg;
	getline(cin, szoveg);

	// 2. feladat
	szoveg = nagybetusit(atalakit(szoveg));

	// 3. feladat
	cout << szoveg << endl;

	// 4. feladat
	string kulcsszo;
	cout << "Kerem a kulcsszot! (maximum 5 ekezetek nelkuli karakter)" << endl;
	cin >> kulcsszo;
	kulcsszo = nagybetusit(kulcsszo);

	// 5. feladat
	string kulcsszoveg = osszefuz(kulcsszo, szoveg);
	cout << kulcsszoveg << endl;

	// 6. feladat
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
		stringstream kodolt_stream;
		for (int i = 0; i < szoveg.length(); i++) {
			kodolt_stream << kodtabla[szoveg[i]-'A'][kulcsszoveg[i]-'A'];
		}
		kodolt = kodolt_stream.str();

		// 7. feladat
		cout << kodolt << endl;
		ofstream fajl_ki;
		fajl_ki.open("kodolt.dat");
		if (fajl_ki.is_open()) {
			fajl_ki << kodolt;
			fajl_ki.close();
		}
		else {
			cout << "Nem sikerult kiirni" << endl;
		}
	}
	else {
		cout << "Nem sikerult beolvasni" << endl;
	}

	

	system("pause");
	return 0;
}

