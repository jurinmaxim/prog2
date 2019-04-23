#ifndef SZIMULACIOIDO_H
#define SZIMULACIOIDO_H

class SzimulacioIdo
{
public:
    ~SzimulacioIdo();
    inline static SzimulacioIdo* getPeldany();
    inline void setIdo(const int ido);
    inline int getIdo() const;
    inline void idoNovel();

private:
    SzimulacioIdo();

    static SzimulacioIdo* peldanyPtr;
    int ido;
};

inline SzimulacioIdo* SzimulacioIdo::getPeldany()
{
    if(!peldanyPtr) {
	peldanyPtr = new SzimulacioIdo;
    }

    return peldanyPtr;
}

inline void SzimulacioIdo::setIdo(const int ido)
{
    this->ido = ido;
}

inline int SzimulacioIdo::getIdo() const
{
    return ido;
}

inline void SzimulacioIdo::idoNovel()
{
    this->ido++;
}

#endif // SZIMULACIOIDO_H
