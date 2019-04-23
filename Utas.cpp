#include "Utas.h"
#include "memtrace.h"

using namespace std;

Utas::Utas()	// Utas konstruktor
{
    this->id = Utas::INVALID;
    this->indulasiIdo = Utas::INVALID;
    this->setStatus(Utas::INVALID, Utas::INVALID);
}
Utas::~Utas()	// Utas destruktor
{
}
void Utas::printStatus() const	// kiirja az utas statusat
{
    switch(this->status) {
    case INVALID: {
	cout << "INVALID";
	break;
    }
    case JELOLT_VAR: {
	cout << "JELOLT_VAR";
	break;
    }
    case FELFELE_VAR: {
	cout << "FELFELE_VAR";
	break;
    }
    case LEFELE_VAR: {
	cout << "LEFELE_VARLEFELE_VAR";
	break;
    }
    case UTAZIK: {
	cout << "UTAZIK";
	break;
    }
    case KESZ: {
	cout << "KESZ";
	break;
    }
    default: {
	throw exception();
	break;
    }
    }
}

void Utas::setStatus(const Utas::Status status, int ido)	//beallitja az utas statusat
{
    this->status = status;

    if(status != Utas::INVALID) {
	if(status == Utas::UTAZIK) {
	    this->beszallasiIdo = ido;
	} else if(status == Utas::KESZ) {
	    this->kiszallasiIdo = ido;
	}
    }
}