// 2005 május.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>		// alap beolvasás, kiírás
#include <fstream>		// fájlkezelés
#include <Windows.h>	// system("pause") parancshoz (csak Windows operációs rendszeren mûködik!)
#include <ctime>		// time() függvényhez

using namespace std;

int main()
{
	srand(time(0));

	int lottoszamok[52][5];

	ifstream fajl_be("lottosz.dat");
	// ha sikerül a fájl megnyitása, beolvasom az adatokat belõle
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
	// egyébként feltöltöm 1 és 90 közötti véletlenszámokkal a "D-s tömböt
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
	// utolsó hét számainak rendezése buborékrendezéses módszerrel
	for (int i = 5 - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (lottoszamok[51][j] > lottoszamok[51][j + 1]) {
				int temp = lottoszamok[51][j];
				lottoszamok[51][j] = lottoszamok[51][j + 1];
				lottoszamok[51][j + 1] = temp;
			}
		}
	}
	// kiírás
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
	// ennek eldöntéséhez statisztikát készítek a számokról,
	// ami azt tartalmazza, hogy melyik számot hányszor húzták ki
	// azért, mert ez a késõbbi feladatok (6, 8, 9) során is hasznos lesz
	// ha ez kész, utána csak azt kell vizsgálnom, volt-e olyan szám, melynek darabszáma 0

	// az átláthatóság kedvéért 91 elemû tömböt hozok létre, hogy 1-90-ig tudjam indexelni
	// az index lesz maga a szám, a hozzátartozó érték pedig az, hogy hányszor húzták ki
	// darabszám, tehát eredetileg 0-ról indítom és ha elõfordul egy szám (pl. 36),
	// akkor a hozzá tartozó értéket (statisztika[36]) eggyel növelem
	int statisztika[91] = { 0 };

	// egyelõre csak az elsõ 51 hetet kell vizsgálni
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 5; j++) {
			statisztika[lottoszamok[i][j]]++;
		}
	}

	// egy logikai változóval jelzem, hogy van-e, ami nem fordult elo
	bool van_ami_nem_fordult_elo = false;
	// egy ciklussal vizsgálom a stisztikát
	// ha van olyan szám, ami nem fordult elõ, tehát a hozzá tartozó darabszám 0,
	// akkor a logikai változómat igazba billentem és nem is kell tovább futnia a ciklusnak
	// egyébként, ha nem találok ilyet, végignézem a teljes statisztikát
	for (int i = 0; !van_ami_nem_fordult_elo && i < 90; i++) {
		if (statisztika[i] == 0) {
			van_ami_nem_fordult_elo = true;
			//cout << i + 1 << " ";
		}
	}

	// ha lefutott a ciklus, vizsgálom, hogy volt-e ilyen szám
	if (van_ami_nem_fordult_elo) {
		cout << "Van";
	}
	else {
		cout << "Nincs";
	}
	cout << endl;


	cout << endl;
	cout << "6. feladat" << endl;
	// a korábbi statisztikámat felhasználom
	int paratlanok_szama = 0;
	// 1-rõl indítom és kettesével lépkedek,
	// így a páratlan számokhoz tartozó darabszámokat összeadom
	for (int i = 1; i <= 90; i += 2) {
		paratlanok_szama += statisztika[i];
	}
	cout << paratlanok_szama << " db paratlan szam volt a kihuzottak kozott." << endl;
	

	cout << endl;
	cout << "7. feladat" << endl;
	//a hozzáfûzést már a beolvasáskor megcsináltam, így csak kiírni kell
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
	// ismét felhasználom a korábban létrehozott statisztikámat
	// most viszont beleveszem az utolsó hét számait is
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
	// felhasználom a megadott prímszámokat
	// a tömb végére -1-et rakok (végjeles sorozat) így tudom, hogy egy ciklussal mikor kell megállnom,
	// mert lusta vagyok megszámolni, hogy ez összesen hány darab szám :)
	int primek[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, -1 };
	// a statisztikához nyúlok most is
	// egészen addig vizsgálom az elemeket, amíg el nem érem a prím tömbben az egyetlen negatív számot, a végjelet
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
