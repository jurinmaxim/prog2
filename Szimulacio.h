#ifndef SZIMULACIO_H
#define SZIMULACIO_H

#include <string>
#include <vector>
#include "Lift.h"
#include "Emelet.h"
#include "Utas.h"

class Szimulacio
{
public:
    Szimulacio();
    ~Szimulacio();
    void hozzaadUtas(const int indulasiIdo, const Emelet& indulasiEmelet, const Emelet& erkezesiEmelet);
    void szimulacioIdoNovel();
    void utasSorbaallit();
    bool osszesUtasKesz() const;
    void liftSzimulacioFuttat();
    void szimulacioFuttat();
    void sorBeolvas(const string& sor, int& indulasiIdo, Emelet& indulasiEmelet, Emelet& erkezesiEmelet) const;
    void adatokBetoltFilebol();
    void statisztikaKiir() const;
    void statisztikaSzamit();
    inline void setLiftAdatFile(const string& liftAdatFile);
    inline int getIdo() const;

    static const int LIFTEK_SZAMA = 5;

private:
    UtasLista* utasListaPtr;
    SzimulacioIdo* szimulacioIdoPtr;
    string liftAdatFile;
    vector<Lift> liftek;
    double atlVarakozasiIdo;
    double atlUtazasiIdo;
};
inline int Szimulacio::getIdo() const
{
    return this->szimulacioIdoPtr->getIdo();
}

inline void Szimulacio::setLiftAdatFile(const string& liftAdatFile)
{
    this->liftAdatFile = liftAdatFile;
}

#endif // SZIMULACIO_H