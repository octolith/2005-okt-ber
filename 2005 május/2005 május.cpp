// 2005 m�jus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>		// alap beolvas�s, ki�r�s
#include <fstream>		// f�jlkezel�s
#include <Windows.h>	// system("pause") parancshoz (csak Windows oper�ci�s rendszeren m�k�dik!)
#include <ctime>		// time() f�ggv�nyhez

using namespace std;

int main()
{
	srand(time(0));

	int lottoszamok[52][5];

	ifstream fajl_be("lottosz.dat");
	// ha siker�l a f�jl megnyit�sa, beolvasom az adatokat bel�le
	if (fajl_be.is_open()) {
		for (int i = 0; i < 51; i++) {
			for (int j = 0; j < 5; j++) {
				fajl_be >> lottoszamok[i][j];
				//cout << lottoszamok[i][j] << " ";
			}
			//cout << endl;
		}
		fajl_be.close();
	}
	// egy�bk�nt felt�lt�m 1 �s 90 k�z�tti v�letlensz�mokkal a "D-s t�mb�t
	else {
		cout << "Nem sikerult a lottosz.dat fajl megynitasa beolvasasra,igy veletlenszamokkal dolgozom." << endl;
		for (int i = 0; i < 51; i++) {
			for (int j = 0; j < 5; j++) {
				rand()%90 + 1 >> lottoszamok[i][j];
				//cout << lottoszamok[i][j] << " ";
			}
			//cout << endl;
		}
	}

	cout << endl;
	cout << "1. feladat" << endl;
	cout << "Kerem az 52. het lottoszamait, szokozzel elvalasztva!" << endl;
	for (int i = 0; i < 5; i++) {
		cin >> lottoszamok[51][i];
	}


	cout << endl;
	cout << "2. feladat" << endl;
	// utols� h�t sz�mainak rendez�se bubor�krendez�ses m�dszerrel
	for (int i = 5 - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (lottoszamok[51][j] > lottoszamok[51][j + 1]) {
				int temp = lottoszamok[51][j];
				lottoszamok[51][j] = lottoszamok[51][j + 1];
				lottoszamok[51][j + 1] = temp;
			}
		}
	}
	// ki�r�s
	for (int i = 0; i < 5; i++) {
		cout << lottoszamok[51][i] << " ";
	}
	cout << endl;


	cout << endl;
	cout << "3. feladat" << endl;
	int het_szama;
	cout << "Adjon meg egy szamot 1 es 51 kozott: ";
	cin >> het_szama;


	cout << endl;
	cout << "4. feladat" << endl;
	for (int i = 0; i < 5; i++) {
		cout << lottoszamok[het_szama - 1][i] << " ";
	}
	cout << endl;


	cout << endl;
	cout << "5. feladat" << endl;
	// ennek eld�nt�s�hez statisztik�t k�sz�tek a sz�mokr�l,
	// ami azt tartalmazza, hogy melyik sz�mot h�nyszor h�zt�k ki
	// az�rt, mert ez a k�s�bbi feladatok (6, 8, 9) sor�n is hasznos lesz
	// ha ez k�sz, ut�na csak azt kell vizsg�lnom, volt-e olyan sz�m, melynek darabsz�ma 0

	// az �tl�that�s�g kedv��rt 91 elem� t�mb�t hozok l�tre, hogy 1-90-ig tudjam indexelni
	// az index lesz maga a sz�m, a hozz�tartoz� �rt�k pedig az, hogy h�nyszor h�zt�k ki
	// darabsz�m, teh�t eredetileg 0-r�l ind�tom �s ha el�fordul egy sz�m (pl. 36),
	// akkor a hozz� tartoz� �rt�ket (statisztika[36]) eggyel n�velem
	int statisztika[91] = { 0 };

	// egyel�re csak az els� 51 hetet kell vizsg�lni
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 5; j++) {
			statisztika[lottoszamok[i][j]]++;
		}
	}

	// egy logikai v�ltoz�val jelzem, hogy van-e, ami nem fordult elo
	bool van_ami_nem_fordult_elo = false;
	// egy ciklussal vizsg�lom a stisztik�t
	// ha van olyan sz�m, ami nem fordult el�, teh�t a hozz� tartoz� darabsz�m 0,
	// akkor a logikai v�ltoz�mat igazba billentem �s nem is kell tov�bb futnia a ciklusnak
	// egy�bk�nt, ha nem tal�lok ilyet, v�gign�zem a teljes statisztik�t
	for (int i = 0; !van_ami_nem_fordult_elo && i < 90; i++) {
		if (statisztika[i] == 0) {
			van_ami_nem_fordult_elo = true;
			//cout << i + 1 << " ";
		}
	}

	// ha lefutott a ciklus, vizsg�lom, hogy volt-e ilyen sz�m
	if (van_ami_nem_fordult_elo) {
		cout << "Van";
	}
	else {
		cout << "Nincs";
	}
	cout << endl;


	cout << endl;
	cout << "6. feladat" << endl;
	// a kor�bbi statisztik�mat felhaszn�lom
	int paratlanok_szama = 0;
	// 1-r�l ind�tom �s kettes�vel l�pkedek,
	// �gy a p�ratlan sz�mokhoz tartoz� darabsz�mokat �sszeadom
	for (int i = 1; i <= 90; i += 2) {
		paratlanok_szama += statisztika[i];
	}
	cout << paratlanok_szama << " db paratlan szam volt a kihuzottak kozott." << endl;
	

	cout << endl;
	cout << "7. feladat" << endl;
	//a hozz�f�z�st m�r a beolvas�skor megcsin�ltam, �gy csak ki�rni kell
	ofstream fajl_ki;
	fajl_ki.open("lotto52.ki");
	if (fajl_ki.is_open()) {
		for (int i = 0; i < 52; i++) {
			for (int j = 0; j < 5; j++) {
				fajl_ki << lottoszamok[i][j] << " ";
			}
			fajl_ki << endl;
		}
		fajl_ki.close();
	}
	else {
		cout << "Nem sikerult a lotto52.ki fajl megynitasa kiirasra." << endl;
	}


	cout << endl;
	cout << "8. feladat" << endl;
	// ism�t felhaszn�lom a kor�bban l�trehozott statisztik�mat
	// most viszont beleveszem az utols� h�t sz�mait is
	for (int i = 0; i < 5; i++) {
		statisztika[lottoszamok[51][i]]++;
	}

	// kiirom a frissitett statisztikat
	for (int i = 1; i <= 90; i++) {
		cout << statisztika[i] << " ";
	}
	cout << endl;


	cout << endl;
	cout << "9. feladat" << endl;
	// felhaszn�lom a megadott pr�msz�mokat
	// a t�mb v�g�re -1-et rakok (v�gjeles sorozat) �gy tudom, hogy egy ciklussal mikor kell meg�llnom,
	// mert lusta vagyok megsz�molni, hogy ez �sszesen h�ny darab sz�m :)
	int primek[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, -1 };
	// a statisztik�hoz ny�lok most is
	// eg�szen addig vizsg�lom az elemeket, am�g el nem �rem a pr�m t�mbben az egyetlen negat�v sz�mot, a v�gjelet
	int i = 0;
	while (primek[i] > 0) {
		// ha az adott primszamot egyszer sem huztak ki, kiirom
		if (statisztika[primek[i]] == 0) {
			cout << primek[i] << " ";
		}
		i++;
	}
	cout << endl;

	cout << endl;
	system("pause");
	return 0;
}
