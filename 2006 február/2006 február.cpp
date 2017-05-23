// 2006 február.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

// az egyszerûbb kezelhetõség kedvéért nem ora, perc, masodperc alakban tarolom az idopontokat, hanem masodpercce alakitva
// a telefonszamot pedig azert stringkent tarolom, mert egyszerubb a kezdetet vizsgalni igy
// es nem kell ugy kezelnem, mintha szam lenne
struct Hivas {
	int kezdete;
	int vege;
	string telefonszam;
};


// atvaltok egy idopontot masodpercbe
int masodpercben(int ora, int perc, int mp) {
	return ora * 3600 + perc * 60 + mp;
}


// eldonti egy hivasrol, hogy csucsidoben trotent-e vagy sem
bool csucsido(Hivas a) {
	// mivel az idopontot masodpercben tarolom, igy a csucsido hatarait (07:00:00 - 18:00:00) is így kell vizsgálnom
	if (a.kezdete >= masodpercben(7, 0, 0) && a.kezdete < masodpercben(18, 0, 0)) {
		//cout << "csucsido" << endl;
		return true;
	}
	else {
		//cout << "nem csucsido" << endl;
		return false;
	}
}


// eldonti egy hivasrol, hogy mobil iranyba tortent-e
bool mobil(Hivas a) {
	// az elso ket karakterbol allo alsztringet vizsgalom .substr() fuggveny segitsegevel
	if (a.telefonszam.substr(0, 2) == "39" || a.telefonszam.substr(0, 2) == "41" || a.telefonszam.substr(0, 2) == "71") {
		//cout << "mobil" << endl;
		return true;
	}
	else {
		//cout << "nem mobil" << endl;
		return false;
	}
}


// megadja, hogy hany perc lett számlázva az adott hívásnál. Minden megkezdett perc számít.
int hivas_hossza(Hivas a) {
	// egész osztás
	int megkezdett_percek = (a.vege - a.kezdete) / 60;

	// ha nem teljes perc jön ki a másodpercekbõl, akkor még egy megkezdett perc van
	if ((a.vege - a.kezdete) % 60 != 0) {
		megkezdett_percek += 1;
	}
	return megkezdett_percek;
}


int main()
{
	Hivas hivasok[200];
	int db = 0;
	ifstream fajl_be("HIVASOK.TXT");
	// ha sikerul a fajlt megnyitni, beolvasom az adatokat
	if (fajl_be.is_open()) {
		// kezdes idopontjanak ideiglenes tarolasahoz
		int k_ora;
		int k_perc;
		int k_mp;
		// befejezes idopontjanak ideiglenes tarolasahoz
		int v_ora;
		int v_perc;
		int v_mp;

		while (fajl_be >> k_ora >> k_perc >> k_mp >> v_ora >> v_perc >> v_mp) {
			// másodperccé alakítom az idõpontokat
			hivasok[db].kezdete = masodpercben(k_ora, k_perc, k_mp);
			hivasok[db].vege = masodpercben(v_ora, v_perc, v_mp);
			// beolvasom a telefonszámot is
			fajl_be >> hivasok[db].telefonszam;

			db++;
		}
		fajl_be.close();
	}
	// ha nem sikerul a fajlt megnyitni, manualisan krealok ket hivast
	else {
		db = 2;

		hivasok[0].kezdete = masodpercben(6, 1, 0);
		hivasok[0].vege = masodpercben(6, 2, 25);
		hivasok[0].telefonszam = "392712621";

		hivasok[1].kezdete = masodpercben(7, 24, 29);
		hivasok[1].vege = masodpercben(7, 33, 13);
		hivasok[1].telefonszam = "166566516";
	}


	cout << endl;
	cout << "1. feladat" << endl;
	// azért Hivas típusú objektumot hozok létre, mert majd a következõ feladatban ebben tárolom az idõpontokat
	// és mert úgy írtam meg a függvényeket, hogy Hivas objektumot kezeljenek :)
	Hivas felhasznalotol;
	cout << "Kerem a telefonszamot!" << endl;
	cin >> felhasznalotol.telefonszam;
	if (mobil(felhasznalotol)) {
		cout << "Mobil" << endl;
	}
	else {
		cout << "Vezetekes" << endl;
	}


	cout << endl;
	cout << "2. feladat" << endl;
	// ora perc mp formában be kell olvasni a hívás kezdetét és a végét
	// mindkettõt másodperccé alakítani és berakni a már létezõ "felhasznalotol" hívásba

	int ora, perc, mp;
	cout << "Adja meg a kezdo idopontot (ora perc masodperc alakban, szokozzel elvalasztva): " << endl;
	cin >> ora >> perc >> mp;
	felhasznalotol.kezdete = masodpercben(ora, perc, mp);
	cout << "Adja meg a befejezo idopontot (ora perc masodperc alakban, szokozzel elvalasztva): " << endl;
	cin >> ora >> perc >> mp;
	felhasznalotol.vege = masodpercben(ora, perc, mp);

	cout << "Szamlazas szempontjabol a hivas " << hivas_hossza(felhasznalotol) << " perces." << endl;
	

	cout << endl;
	cout << "3. feladat" << endl;
	ofstream fajl_ki("percek.txt");
	if (fajl_ki.is_open()) {
		for (int i = 0; i < db; i++) {
			fajl_ki << hivas_hossza(hivasok[i]) << " " << hivasok[i].telefonszam << endl;
			//cout << hivas_hossza(hivasok[i]) << " " << hivasok[i].telefonszam << endl;
		}
		fajl_ki.close();
	}
	else {
		cout << "Nem sikerult kiirni a percek szamat" << endl;
	}


	cout << endl;
	cout << "4. feladat" << endl;
	// egyszerû számlálás tétele, a korábbi csucsido() fuggveny felhasznalasaval
	int csucsideju_hivasok_szama = 0;
	for (int i = 0; i < db; i++) {
		if (csucsido(hivasok[i])) {
			csucsideju_hivasok_szama++;
		}
	}

	cout << csucsideju_hivasok_szama << " db hivas volt csucsidoben, es " << db - csucsideju_hivasok_szama << " db hivas volt csucsidon kivul." << endl;


	cout << endl;
	cout << "5. feladat" << endl;
	// egyszerû összegzés tétele
	int mobil_percek = 0;
	int vezetekes_percek = 0;
	for (int i = 0; i < db; i++) {
		if (mobil(hivasok[i])) {
			mobil_percek += hivas_hossza(hivasok[i]);
		}
		else {
			vezetekes_percek += hivas_hossza(hivasok[i]);
		}
	}

	cout << mobil_percek << " percet beszelt mobil szammal, es " << vezetekes_percek << " percet vezetekessel." << endl;


	cout << endl;
	cout << "6. feladat" << endl;
	double mobil_percdij_csucsidoben = 69.175;
	double vezetekes_percdij_csucsidoben = 30.0;
	double osszesen = 0.0;
	for (int i = 0; i < db; i++) {
		if (csucsido(hivasok[i])) {
			if (mobil(hivasok[i])) {
				osszesen += hivas_hossza(hivasok[i]) * mobil_percdij_csucsidoben;
			}
			else {
				osszesen += hivas_hossza(hivasok[i]) * vezetekes_percdij_csucsidoben;
			}
		}
	}

	cout << "A felhasznalonak osszesen " << osszesen << " forintot kell fizetnie a csucsdijas hivasokert." << endl;

	cout << endl;
	system("pause");
	return 0;
}