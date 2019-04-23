#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Szimulacio.h"
#include "memtrace.h"


Szimulacio::Szimulacio() // Szimulacio konstrukor
{
    this->liftAdatFile = "";
    this->utasListaPtr = UtasLista::getPeldany();
    this->szimulacioIdoPtr = SzimulacioIdo::getPeldany();
    this->liftek.resize(Szimulacio::LIFTEK_SZAMA);
}

Szimulacio::~Szimulacio() //Szimulacio destruktor
{
}

bool Szimulacio::osszesUtasKesz() const	//ellenorzi, hogy kesz van-e az osszes utas
{
    bool kesz = true;
    int utasokSzama = this->utasListaPtr->getUtasListaSize();

    for(int utasIndex = 0; utasIndex < utasokSzama; ++utasIndex) {
	if(this->utasListaPtr->getUtasStatus(utasIndex) != Utas::KESZ) {
	    kesz = false;
	    break;
	}
    }
    return kesz;
}
void Szimulacio::statisztikaKiir() const	//kiirja a statisztikat
{
    cout << endl << "-----------------------------------------------" << endl;
    cout << "Statisztika: " << endl;
    cout << "atlagos utazasi ido: ";
    cout << this->atlVarakozasiIdo << " mp" << endl;
    cout << "atlagos varakozasi ido: ";
    cout << this->atlUtazasiIdo << " mp" << endl;
}
void Szimulacio::statisztikaSzamit()	//kiszamitja a statisztikat
{
    double atlUtazasiIdo = 0;
    double atlVarakozasiIdo = 0;
    int sumUtazasiIdo = 0;
    int sumVarakozasiIdo = 0;
    int beszallasiIdo = 0;
    int kiszallasiIdo = 0;
    int indulasiIdo = 0;
    int utazasiIdo = 0;
    int varakozasiIdo = 0;
    int utasokSzama = 0;

    utasokSzama = this->utasListaPtr->getUtasListaSize();

    for(int utasIndex = 0; utasIndex < utasokSzama; ++utasIndex) {

	indulasiIdo = this->utasListaPtr->getUtasIndulasiIdo(utasIndex);
	beszallasiIdo = this->utasListaPtr->getUtasBeszallasiIdo(utasIndex);
	kiszallasiIdo = this->utasListaPtr->getUtasKiszallasiIdo(utasIndex);

	varakozasiIdo = beszallasiIdo - indulasiIdo;
	utazasiIdo = kiszallasiIdo - beszallasiIdo;

	sumVarakozasiIdo += varakozasiIdo;
	sumUtazasiIdo += utazasiIdo;

	if(this->utasListaPtr->getUtasStatus(utasIndex) != Utas::KESZ) {
	    throw exception();
	}
    }

    atlVarakozasiIdo = (double)sumVarakozasiIdo / (double)utasokSzama;
    atlUtazasiIdo = (double)sumUtazasiIdo / (double)utasokSzama;

    this->atlVarakozasiIdo = atlVarakozasiIdo;
    this->atlUtazasiIdo = atlUtazasiIdo;
}
void Szimulacio::adatokBetoltFilebol()	//betolti az utasok adatait egy filebol
{
    string sor = "";
    ifstream file(this->liftAdatFile.c_str(), ios::in);

    if(file) {
	getline(file, sor);
	while(!file.eof()) {
	    getline(file, sor);
	    if(sor != "") {
		int indulasiIdo;
		Emelet indulasiEmelet;
		Emelet erkezesiEmelet;
		this->sorBeolvas(sor, indulasiIdo, indulasiEmelet, erkezesiEmelet);
		this->hozzaadUtas(indulasiIdo, indulasiEmelet, erkezesiEmelet);
	    }
	}
    } else {
	throw exception();
    }
}

void Szimulacio::hozzaadUtas(const int indulasiIdo, const Emelet& indulasiEmelet, const Emelet& erkezesiEmelet) // hozzaadja az utast az utaslistahoz
{
    Utas utas;
    utas.setId(utasListaPtr->getUtasListaSize());
    utas.setIndulasiIdo(indulasiIdo);
    utas.setIndulasiEmelet(indulasiEmelet);
    utas.setErkezesiEmelet(erkezesiEmelet);
    utas.setStatus(Utas::INVALID, indulasiIdo);

    utasListaPtr->hozzaadUtas(utas);
}

void Szimulacio::sorBeolvas(const string& sor, int& indulasiIdo, Emelet& indulasiEmelet, Emelet& erkezesiEmelet) const	// beolvas egy sort a filebol
{
    int elsoVesszo;
    int masodikVesszo;

    string indulasiIdoStr = "";
    string indulasiEmeletStr = "";
    string erkezesiEmeletStr = "";

    elsoVesszo = sor.find(",");
    masodikVesszo = sor.find(",", elsoVesszo + 1);

    indulasiIdoStr = sor.substr(0, elsoVesszo);
    indulasiIdo = atoi(indulasiIdoStr.c_str());

    indulasiEmeletStr = sor.substr(elsoVesszo + 1, masodikVesszo - 2);
    indulasiEmelet.setSzam(atoi(indulasiEmeletStr.c_str()));

    erkezesiEmeletStr = sor.substr(masodikVesszo + 1);
    erkezesiEmelet.setSzam(atoi(erkezesiEmeletStr.c_str()));
}

void Szimulacio::szimulacioIdoNovel()	// noveli a szimulacio idejet (1 masodperccel)
{
    this->szimulacioIdoPtr->idoNovel();
    this->utasSorbaallit();
}

void Szimulacio::utasSorbaallit()	// ha az utas odaert a lifthez, sorbaallitja ot
{
    int erkezesiEmeletSzam = -1;
    int indulasiEmeletSzam = -1;
    int ido = this->getIdo();
    int utasokSzama = this->utasListaPtr->getUtasListaSize();

    for(int utasIndex = 0; utasIndex < utasokSzama; ++utasIndex) {
	if(this->utasListaPtr->getUtasIndulasiIdo(utasIndex) == ido) {
	    indulasiEmeletSzam = this->utasListaPtr->getUtasIndulasiEmeletSzam(utasIndex);
	    erkezesiEmeletSzam = this->utasListaPtr->getUtasErkezesiEmeletSzam(utasIndex);

	    if(indulasiEmeletSzam < erkezesiEmeletSzam) {
		this->utasListaPtr->setUtasStatus(utasIndex, Utas::FELFELE_VAR, ido);
	    } else {
		this->utasListaPtr->setUtasStatus(utasIndex, Utas::LEFELE_VAR, ido);
	    }
	}
    }
}

void Szimulacio::liftSzimulacioFuttat()	// beolvassa az adatokat, lefuttatja a szimulaciot es kiirja a statisztikat
{
    this->setLiftAdatFile("utasok.txt");
    this->adatokBetoltFilebol();

    for(int aktLift = 0; aktLift < LIFTEK_SZAMA; ++aktLift) {
	this->liftek[aktLift].setNev("Lift ", aktLift);
    }
    cout << "Szimulacio futtatasa..." << endl;
    this->szimulacioFuttat();
    this->statisztikaSzamit();
    this->statisztikaKiir();
	
	delete this->szimulacioIdoPtr;
	delete this->utasListaPtr;
}
void Szimulacio::szimulacioFuttat()	//lefuttatja a szimulaciot
{
    while(!this->osszesUtasKesz()) {
	for(int aktLift = 0; aktLift < LIFTEK_SZAMA; ++aktLift) {
	    this->liftek[aktLift].kovetkezoLepes();
	}
	this->szimulacioIdoNovel();
    }
}

int main()
{
    try {
	Szimulacio szimulacio;
	szimulacio.liftSzimulacioFuttat();
    } catch(const exception& e) {
	cout << e.what() << endl;
	cout << "Hiba tortent!" << endl;
    }
    return 0;
}
