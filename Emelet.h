#ifndef EMELET_H
#define EMELET_H

class Emelet
{
public:
    Emelet();
    ~Emelet();
    inline void emeletSzamNovel();
    inline void emeletSzamCsokkent();
    inline void setSzam(const int szam);
    inline int getSzam() const;
    static const int ELSO_SZINT = 0;

private:
    int szam;
};

inline void Emelet::emeletSzamNovel()
{
    this->szam++;
}

inline void Emelet::emeletSzamCsokkent()
{
    this->szam--;
}

inline void Emelet::setSzam(const int szam)
{
    this->szam = szam;
}

inline int Emelet::getSzam() const
{
    return this->szam;
}

#endif // EMELET_H
