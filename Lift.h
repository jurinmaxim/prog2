#ifndef Lift_h
#define Lift_h

#include <list>
#include <sstream>
#include "Utas.h"
#include "UtasLista.h"
#include "SzimulacioIdo.h"

class Lift
{
public:
    enum LiftStatus { INVALID = -1, ALL_NINCS_UTAS, ALL_FELFELE, ALL_LEFELE, MEGY_FELFELE, MEGY_LEFELE };
    Lift();
    ~Lift();
    void hozzaadUtas(const int index);
    void eltavolitUtas(const int index);
    void ellUtasBeszall(const bool felMegy);
    void ellUtasKiszall(const bool felMegy);
    void beszallitUtasok();
    void kiszallitUtasok();
    int maxErkezesiSzintUtas() const;
    int minErkezesiSzintUtas() const;
    void UtazFel(const int emeletSzam);
    void UtazLe(const int emeletSzam);
    void UtazCelFele();
    void ujCelUtasSzamit();
    void kovCelUtasSzamit();
    bool ellCelUtasBentVan() const;
    void kovetkezoLepes();
    Utas::Status getUtasStatus();
    void setLiftStatusAll(const bool felMegy);
    void liftMozog(const bool felMegy);
    void liftAll();
    void printLiftStatus() const;
    void printEsemeny(const string& esemeny, const int index) const;
    void printUtasIdk() const;

    inline int getIdo() const;
    inline void setCelUtasIndex(const int index);
    inline void setLiftStatus(const Lift::LiftStatus liftStatus);
    inline void setNev(const string& nev, const int index);
    inline void getNev(string& nev) const;

    static const int MAX_UTAS = 10;
    static const int KOV_EMELET_IDO = 6;

private:
    Emelet aktEmelet;
    Emelet celEmelet;
    int celUtasIndex;
    LiftStatus liftStatus;
    string nev;
    UtasLista* utasListaPtr;
    SzimulacioIdo* szimulacioIdoPtr;
    list<int> utasIdk;
    vector<int> beszallLista;
    vector<int> kiszallLista;
    int utazIdo;
    int kovEmeletIdo;
};

inline void Lift::getNev(string& nev) const
{
    nev = this->nev;
}

inline int Lift::getIdo() const
{
    return this->szimulacioIdoPtr->getIdo();
}

inline void Lift::setCelUtasIndex(const int index)
{
    this->celUtasIndex = index;
}

inline void Lift::setLiftStatus(const Lift::LiftStatus liftStatus)
{
    this->liftStatus = liftStatus;
}

inline void Lift::setNev(const string& nev, const int index)
{
    std::stringstream sstm;
    sstm << nev << index;
    this->nev = sstm.str();
}

#endif