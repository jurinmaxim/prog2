#ifndef UTASLISTA_H
#define UTASLISTA_H

#include <vector>
#include "Utas.h"

using namespace std;

class UtasLista
{
public:
    ~UtasLista();
    bool getKovCelUtasIndex(const int ido,
        const Emelet& aktsemelet,
        const Emelet& erkezesiEmelet,
        const Utas::Status status,
        int& kovUtasIndex);
    bool getSorbanalloUtasokEmeleten(const int ido,
        const Emelet& aktEmelet,
        const Utas::Status status,
        const int celUtasIndex,
        vector<int>& beszallLista);
    inline static UtasLista* getPeldany();
    inline void hozzaadUtas(const Utas& utas);
    inline int getUtasIndulasiIdo(const int index) const;
    inline int getUtasBeszallasiIdo(const int index) const;
    inline int getUtasKiszallasiIdo(const int index) const;
    inline int getUtasId(const int index) const;
    inline int getUtasListaSize() const;
    inline int getUtasIndulasiEmeletSzam(const int index) const;
    inline int getUtasErkezesiEmeletSzam(const int index) const;
    inline void setUtasStatus(const int index, Utas::Status status, const int ido);
    inline Utas::Status getUtasStatus(const int index) const;

private:
    UtasLista();
    static UtasLista* peldanyPtr;
    vector<Utas> utasLista;
};

inline void UtasLista::hozzaadUtas(const Utas& utas)
{
    this->utasLista.push_back(utas);
}

inline UtasLista* UtasLista::getPeldany()
{
    if(!peldanyPtr) {
	peldanyPtr = new UtasLista;
    }

    return peldanyPtr;
}

inline int UtasLista::getUtasBeszallasiIdo(const int index) const
{
    return this->utasLista.at(index).getBeszallasiIdo();
}

inline int UtasLista::getUtasErkezesiEmeletSzam(const int index) const
{
    return this->utasLista.at(index).getErkezesiEmeletSzam();
}

inline int UtasLista::getUtasKiszallasiIdo(const int index) const
{
    return this->utasLista.at(index).getKiszallasiIdo();
}

inline int UtasLista::getUtasId(const int index) const
{
    return this->utasLista.at(index).getId();
}

inline int UtasLista::getUtasListaSize() const
{
    return this->utasLista.size();
}

inline int UtasLista::getUtasIndulasiEmeletSzam(const int index) const
{
    return this->utasLista.at(index).getIndulasiEmeletSzam();
}

inline int UtasLista::getUtasIndulasiIdo(const int index) const
{
    return this->utasLista.at(index).getIndulasiIdo();
}

inline Utas::Status UtasLista::getUtasStatus(const int index) const
{
    return this->utasLista.at(index).getStatus();
}

inline void UtasLista::setUtasStatus(const int index, Utas::Status status, const int ido)
{
    this->utasLista.at(index).setStatus(status, ido);
}

#endif // UTASLISTA_H
