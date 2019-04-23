#ifndef UTAS_H
#define UTAS_H

#include <iostream>
#include <string>
#include "Emelet.h"

class Utas
{
public:
    enum Status { INVALID = -1, JELOLT_VAR, FELFELE_VAR, LEFELE_VAR, UTAZIK, KESZ };

    Utas();
    ~Utas();

    inline int getBeszallasiIdo() const;
    inline int getKiszallasiIdo() const;
    inline void setIndulasiIdo(const int indulasiIdo);
    inline int getIndulasiIdo() const;
    inline int getErkezesiIdo() const;
    inline int getIndulasiEmeletSzam() const;
    inline int getErkezesiEmeletSzam() const;
    inline int getId() const;
    inline void setId(const int id);
    inline void getIndulasiEmelet(Emelet& indulasiEmelet) const;
    inline void setIndulasiEmelet(const Emelet& indulasiEmelet);
    inline void getErkezesiEmelet(Emelet& erkezesiEmelet) const;
    inline void setErkezesiEmelet(const Emelet& erkezesiEmelet);
    inline Utas::Status getStatus() const;
    void setStatus(const Utas::Status status, int ido);
    void printStatus() const;

private:
    int id;
    int indulasiIdo;
    int beszallasiIdo;
    int kiszallasiIdo;
    Emelet indulasiEmelet;
    Emelet erkezesiEmelet;
    Status status;
};
inline int Utas::getBeszallasiIdo() const
{
    return this->beszallasiIdo;
}

inline void Utas::getErkezesiEmelet(Emelet& erkezesiEmelet) const
{
    erkezesiEmelet = this->erkezesiEmelet;
}

inline int Utas::getErkezesiEmeletSzam() const
{
    return this->erkezesiEmelet.getSzam();
}

inline int Utas::getKiszallasiIdo() const
{
    return this->kiszallasiIdo;
}

inline int Utas::getId() const
{
    return this->id;
}

inline int Utas::getIndulasiIdo() const
{
    return this->indulasiIdo;
}

inline void Utas::getIndulasiEmelet(Emelet& indulasiEmelet) const
{
    indulasiEmelet = this->indulasiEmelet;
}

inline int Utas::getIndulasiEmeletSzam() const
{
    return this->indulasiEmelet.getSzam();
}

inline Utas::Status Utas::getStatus() const
{
    return this->status;
}

inline void Utas::setErkezesiEmelet(const Emelet& erkezesiEmelet)
{
    this->erkezesiEmelet = erkezesiEmelet;
}

inline void Utas::setId(const int id)
{
    this->id = id;
}

inline void Utas::setIndulasiEmelet(const Emelet& indulasiEmelet)
{
    this->indulasiEmelet = indulasiEmelet;
}

inline void Utas::setIndulasiIdo(const int indulasiIdo)
{
    this->indulasiIdo = indulasiIdo;
}

#endif // UTAS_H
