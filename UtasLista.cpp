#include "UtasLista.h"
#include "memtrace.h"

UtasLista* UtasLista::peldanyPtr = 0;

UtasLista::UtasLista()	// UtasLista konstruktor
{
}
UtasLista::~UtasLista()	// UtasLista destruktor
{
}
bool UtasLista::getKovCelUtasIndex(const int ido,	 // megkeresi a kovetkezo celutas indexet
    const Emelet& aktEmelet,
    const Emelet& erkezesiEmelet,
    const Utas::Status status,
    int& kovUtasIndex)
{
    bool siker = false;
    int utasokSzama = this->utasLista.size();

    for(int utasIndex = 0; utasIndex < utasokSzama; ++utasIndex) {
	Utas aktUtas = this->utasLista.at(utasIndex);

	if(aktUtas.getStatus() == Utas::INVALID || aktUtas.getStatus() == Utas::JELOLT_VAR ||
	    aktUtas.getStatus() == Utas::UTAZIK || aktUtas.getStatus() == Utas::KESZ) {
	    continue;
	}

	if((status == aktUtas.getStatus() || status == Utas::INVALID) && aktUtas.getStatus() != Utas::JELOLT_VAR) {
	    if(ido >= aktUtas.getIndulasiIdo()) {
		Emelet indulasiEmelet;
		aktUtas.getIndulasiEmelet(indulasiEmelet);

		if((aktEmelet.getSzam() <= indulasiEmelet.getSzam() &&
		        erkezesiEmelet.getSzam() >= indulasiEmelet.getSzam()) ||
		    status == Utas::INVALID) {

		    kovUtasIndex = aktUtas.getId();
		    siker = true;

		    break;
		}
	    }
	}
    }

    return siker;
}

bool UtasLista::getSorbanalloUtasokEmeleten(const int ido,	// sorba allitja az utasokat az emeleten
    const Emelet& aktEmelet,
    const Utas::Status status,
    const int celUtasIndex,
    vector<int>& beszallLista)
{
    bool siker = false;
    int utasokSzama = 0;

    utasokSzama = this->utasLista.size();

    for(int utasIndex = 0; utasIndex < utasokSzama; ++utasIndex) {
	Utas aktUtas = this->utasLista.at(utasIndex);

	if(aktUtas.getStatus() == Utas::KESZ) {
	    continue;
	}

	if(status == aktUtas.getStatus() || celUtasIndex == utasIndex) {

	    if(ido >= aktUtas.getIndulasiIdo()) {

		Emelet aktIndulasiEmelet;
		aktUtas.getIndulasiEmelet(aktIndulasiEmelet);

		if(aktEmelet.getSzam() == aktIndulasiEmelet.getSzam()) {

		    beszallLista.push_back(aktUtas.getId());
		    siker = true;
		}
	    }
	}
    }

    return siker;
}
