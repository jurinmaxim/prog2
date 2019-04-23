#include <iostream>
#include "Lift.h"
#include "memtrace.h"

Lift::Lift()	//Lift Konstruktor
{
    this->setLiftStatus(Lift::ALL_NINCS_UTAS);
    this->utasListaPtr = UtasLista::getPeldany();
    this->szimulacioIdoPtr = SzimulacioIdo::getPeldany();
    this->nev = "";
    this->kovEmeletIdo = KOV_EMELET_IDO;
    this->utazIdo = Lift::INVALID;
    this->setCelUtasIndex(Lift::INVALID);
}
Lift::~Lift()	//Lift Destruktor
{
}
void Lift::hozzaadUtas(const int index)	//beszallitja az utast a liftbe
{
    this->printEsemeny(" beszallt", index);
    this->utasIdk.push_back(index);
    this->utasListaPtr->setUtasStatus(index, Utas::UTAZIK, this->getIdo());

    if(this->celUtasIndex == Lift::INVALID) {
	this->setCelUtasIndex(index);
	if(utasIdk.size() != 1) {
	    throw exception();
	}
    }

    this->printUtasIdk();

    if(this->utasIdk.size() > Lift::MAX_UTAS) {
	throw exception();
    }
    if(this->utasIdk.size() == Lift::MAX_UTAS && !this->ellCelUtasBentVan()) {
	throw exception();
    }
}

void Lift::ellUtasKiszall(const bool felMegy) //ellenorzi, hogy van-e kiszallo utas a szinten
{
    int erkezesiEmeletSzam = Lift::INVALID;
    int id = Lift::INVALID;

    list<int>::const_iterator iter;
    if(this->utasIdk.size() > 0) {

	for(iter = utasIdk.begin(); iter != utasIdk.end(); iter++) {
	    erkezesiEmeletSzam = this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter);
	    id = this->utasListaPtr->getUtasId(*iter);
	    if(this->aktEmelet.getSzam() == erkezesiEmeletSzam) {
		this->kiszallLista.push_back(id);
	    }
	}
    }

    if(!this->kiszallLista.empty()) {
	this->setLiftStatusAll(felMegy);
    }
}
void Lift::ujCelUtasSzamit()	//uj celutast szamol ki
{
    bool siker = false;
    int kovUtasIndex = Lift::INVALID;
    Utas::Status status = Utas::INVALID;

    if(this->celUtasIndex == Lift::INVALID) {
	siker = true;
    }
    status = this->getUtasStatus();

    if(this->utasListaPtr->getKovCelUtasIndex(this->getIdo(), this->aktEmelet, this->celEmelet, status, kovUtasIndex)) {
	if(siker && kovUtasIndex != Lift::INVALID) {
	    this->setCelUtasIndex(kovUtasIndex);
	    this->utasListaPtr->setUtasStatus(kovUtasIndex, Utas::JELOLT_VAR, this->getIdo());
	}
    }
}

void Lift::ellUtasBeszall(const bool felMegy)	//ellenorzi, hogy van-e beszallo utas az adott szinten
{
    Utas::Status status = Utas::INVALID;
    if(felMegy) {
	status = Utas::FELFELE_VAR;
    } else {
	status = Utas::LEFELE_VAR;
    }
    this->utasListaPtr->getSorbanalloUtasokEmeleten(
        this->getIdo(), this->aktEmelet, status, this->celUtasIndex, this->beszallLista);

    if(!this->beszallLista.empty()) {
	this->setLiftStatusAll(felMegy);
    }
}

void Lift::kovCelUtasSzamit()	//kiszamitja a kovetkezo celutast
{
    list<int>::const_iterator iter;
    bool felMegy = false;

    switch(this->liftStatus) {
    case ALL_FELFELE:
    case MEGY_FELFELE: {
	felMegy = true;
	break;
    }
    case ALL_LEFELE:
    case MEGY_LEFELE: {
	felMegy = false;
	break;
    }
    default: {
	throw exception();
	break;
    }
    }
    if(felMegy) {
	bool felMegyFolytat = false;
	for(iter = utasIdk.begin(); iter != utasIdk.end(); iter++) {
	    if(this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter) > this->aktEmelet.getSzam()) {
		felMegyFolytat = true;
		break;
	    }
	}

	if(felMegyFolytat) {
	    this->setCelUtasIndex(maxErkezesiSzintUtas());
	} else {
	    this->setCelUtasIndex(minErkezesiSzintUtas());
	}
    }

    else {
	bool leMegyFolytat = false;

	for(iter = utasIdk.begin(); iter != utasIdk.end(); iter++) {
	    if(this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter) < this->aktEmelet.getSzam()) {
		leMegyFolytat = true;
		break;
	    }
	}

	if(leMegyFolytat) {
	    this->setCelUtasIndex(minErkezesiSzintUtas());
	} else {
	    this->setCelUtasIndex(maxErkezesiSzintUtas());
	}
    }
}

int Lift::maxErkezesiSzintUtas() const	// a maximalis erkezesi szintu utas indexet keresi meg
{
    list<int>::const_iterator iter;
    bool elsoUtas = true;
    int maxEmelet = Lift::INVALID;
    int utasId = Lift::INVALID;

    for(iter = utasIdk.begin(); iter != utasIdk.end(); iter++) {
	if(this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter) > maxEmelet || elsoUtas) {
	    maxEmelet = this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter);
	    utasId = this->utasListaPtr->getUtasId(*iter);
	    elsoUtas = false;
	}
    }
    return utasId;
}

int Lift::minErkezesiSzintUtas() const	// a minimalis erkezesi szintu utas indexet keresi meg
{
    list<int>::const_iterator iter;
    bool elsoUtas = true;
    int minEmelet = Lift::INVALID;
    int utasId = Lift::INVALID;

    for(iter = utasIdk.begin(); iter != utasIdk.end(); iter++) {
	if(this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter) < minEmelet || elsoUtas) {
	    minEmelet = this->utasListaPtr->getUtasErkezesiEmeletSzam(*iter);
	    utasId = this->utasListaPtr->getUtasId(*iter);
	    elsoUtas = false;
	}
    }
    return utasId;
}

void Lift::kovetkezoLepes()	//a lift eldonti az adott idopillanatban, hogy mit csinal
{
    switch(this->liftStatus) {
    case ALL_NINCS_UTAS: {
	this->ujCelUtasSzamit();
	this->UtazCelFele();
	break;
    }
    case ALL_FELFELE:
    case ALL_LEFELE: {
	this->liftAll();
	break;
    }
    case MEGY_FELFELE: {
	bool felMegy = true;
	this->liftMozog(felMegy);
	break;
    }
    case MEGY_LEFELE: {
	bool felMegy = false;
	this->liftMozog(felMegy);
	break;
    }
    case INVALID:
    default: {
	throw exception();
	break;
    }
    }
}

void Lift::kiszallitUtasok()	//kiszallitja a kiszallasra varo utasokat
{
    int utasSzam = this->kiszallLista.size();
    for(int utasIndex = 0; utasIndex < utasSzam; ++utasIndex) {

	this->eltavolitUtas(this->kiszallLista[utasIndex]);
    }

    this->kiszallLista.clear();
}

Utas::Status Lift::getUtasStatus()	//visszaadja az utas statusat
{
    Utas::Status status = Utas::INVALID;

    switch(this->liftStatus) {
    case ALL_NINCS_UTAS: {
	status = Utas::INVALID;
	break;
    }
    case ALL_FELFELE:
    case ALL_LEFELE: {
	if(this->celUtasIndex == Lift::INVALID) {
	    throw exception();
	} else {
	    if(this->ellCelUtasBentVan()) {
		if(this->aktEmelet.getSzam() < this->utasListaPtr->getUtasErkezesiEmeletSzam(this->celUtasIndex)) {
		    status = Utas::FELFELE_VAR;
		} else if(this->aktEmelet.getSzam() >
		    this->utasListaPtr->getUtasErkezesiEmeletSzam(this->celUtasIndex)) {
		    status = Utas::LEFELE_VAR;
		} else {
		    throw exception();
		}
	    } else {
		if(this->aktEmelet.getSzam() < this->utasListaPtr->getUtasIndulasiEmeletSzam(this->celUtasIndex)) {
		    status = Utas::FELFELE_VAR;
		} else if(this->aktEmelet.getSzam() >
		    this->utasListaPtr->getUtasIndulasiEmeletSzam(this->celUtasIndex)) {
		    status = Utas::LEFELE_VAR;
		} else {
		    throw exception();
		}
	    }
	}

	break;
    }
    case MEGY_FELFELE: {
	status = Utas::FELFELE_VAR;
	break;
    }
    case MEGY_LEFELE: {
	status = Utas::LEFELE_VAR;
	break;
    }
    default: {
	throw exception();
	break;
    }
    }

    return status;
}

void Lift::liftMozog(const bool felMegy) //elvegzi a lift mozgas kozbeni teendoit
{

    if(0 == this->utazIdo) {
	this->setLiftStatusAll(felMegy);
    } else {
	this->utazIdo--;

	if(0 == this->utazIdo % this->kovEmeletIdo) {
	    if(felMegy) {
		this->aktEmelet.emeletSzamNovel();
	    } else {
		this->aktEmelet.emeletSzamCsokkent();
	    }
	    this->ellUtasKiszall(felMegy);
	    this->ellUtasBeszall(felMegy);
	}
    }
}

void Lift::liftAll()	//elvegzi a lift allo allapotban levo teendoit
{
    this->beszallitUtasok();
    this->kiszallitUtasok();
    this->UtazCelFele();
}

bool Lift::ellCelUtasBentVan() const	// ellenorzi, hogy bent van-e celutas
{
    list<int>::const_iterator iter;
    bool bentVan = false;
    for(iter = utasIdk.begin(); iter != utasIdk.end(); iter++) {
	if(this->utasListaPtr->getUtasId(*iter) == this->celUtasIndex) {
	    bentVan = true;
	    break;
	}
    }
    return bentVan;
}

void Lift::UtazLe(const int emeletSzam)	//lefele utaz a lift
{
    this->setLiftStatus(Lift::MEGY_LEFELE);
    this->utazIdo = emeletSzam * this->kovEmeletIdo + this->kovEmeletIdo;
}

void Lift::UtazFel(const int emeletSzam)	//felfele utaz a lift
{
    this->setLiftStatus(Lift::MEGY_FELFELE);
    this->utazIdo = emeletSzam * this->kovEmeletIdo + this->kovEmeletIdo;
}

void Lift::UtazCelFele()	//cel fele utaz a lift
{
    if(this->celUtasIndex != Lift::INVALID) {
	int celEmeletSzam = Lift::INVALID;
	if(this->ellCelUtasBentVan()) {
	    celEmeletSzam = this->utasListaPtr->getUtasErkezesiEmeletSzam(this->celUtasIndex);
	} else {
	    celEmeletSzam = this->utasListaPtr->getUtasIndulasiEmeletSzam(this->celUtasIndex);
	}
	if(this->aktEmelet.getSzam() < celEmeletSzam) {
	    this->UtazFel(celEmeletSzam - this->aktEmelet.getSzam());

	} else {
	    this->UtazLe(this->aktEmelet.getSzam() - celEmeletSzam);
	}
    }
}

void Lift::beszallitUtasok()	//beszallitja a beszallasra varo utasokat
{
    int utasSzam = this->beszallLista.size();
    for(int utasIndex = 0; utasIndex < utasSzam; ++utasIndex) {
	if(this->utasIdk.size() == Lift::MAX_UTAS - 1 && !this->ellCelUtasBentVan()) {
	    if(this->beszallLista[utasIndex] == this->celUtasIndex) {
		this->hozzaadUtas(this->beszallLista[utasIndex]);
	    }
	} else if(this->utasIdk.size() < Lift::MAX_UTAS) {
	    this->hozzaadUtas(this->beszallLista[utasIndex]);
	}
    }
    if(this->utasIdk.size() > Lift::MAX_UTAS) {
	throw exception();
    }
    this->beszallLista.clear();
}
void Lift::printLiftStatus() const	//kiirja a lift statusat
{
    switch(this->liftStatus) {
    case INVALID: {
	cout << "INVALID";
	break;
    }
    case ALL_NINCS_UTAS: {
	cout << "ALL_NINCS_UTAS";
	break;
    }
    case ALL_FELFELE: {
	cout << "ALL_FELFELE";
	break;
    }
    case ALL_LEFELE: {
	cout << "ALL_LEFELE";
	break;
    }
    case MEGY_FELFELE: {
	cout << "MEGY_FELFELE";
	break;
    }
    case MEGY_LEFELE: {
	cout << "MEGY_LEFELE";
	break;
    }
    default: {
	throw exception();
	break;
    }
    }
}

void Lift::printEsemeny(const string& esemeny, const int index) const	//kiirja az adott esemenyt
{
    cout << this->nev;
    cout << esemeny;
    cout << " Utas: " << index;
    cout << " Emelet: " << this->aktEmelet.getSzam();
    cout << " Ido: " << this->getIdo() << " mp";
    cout << endl;
}

void Lift::printUtasIdk() const	//kiirja az utasok id-jait, akik a liftben vannak (a celutas csillaggal van jelolve)
{
    cout << "   " << this->nev << " Utasok: [ ";

    list<int>::const_iterator iter;

    for(iter = this->utasIdk.begin(); iter != this->utasIdk.end(); iter++) {
	cout << *iter;

	if(*iter == this->celUtasIndex) {
	    cout << "*";
	}

	cout << " ";
    }

    cout << "]" << endl;
}

void Lift::eltavolitUtas(const int index)	//kiszallitja az utast a liftbol
{
    this->printEsemeny(" kiszallt", index);
    this->utasIdk.remove(index);
    this->utasListaPtr->setUtasStatus(index, Utas::KESZ, this->getIdo());

    if(index == this->celUtasIndex) {
	this->setCelUtasIndex(Lift::INVALID);
	this->kovCelUtasSzamit();
    }

    this->printUtasIdk();

    if(this->utasIdk.empty()) {
	this->setLiftStatus(Lift::ALL_NINCS_UTAS);
    }
}

void Lift::setLiftStatusAll(const bool felMegy)	//megallitja a liftet
{
    if(felMegy) {
	this->setLiftStatus(Lift::ALL_FELFELE);
    } else {
	this->setLiftStatus(Lift::ALL_LEFELE);
    }
}
