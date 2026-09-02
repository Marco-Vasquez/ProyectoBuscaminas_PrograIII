#ifndef CELDA_H
#define CELDA_H

class Celda
{
public:
    Celda();
    void ponerMina();
    bool tieneMina() const;
    void revelar();
    bool estaRevelada() const; //const porque no modifica los atributos del objeto
    void alternarBandera();
    bool tieneBandera() const;
    void setMinasVecinas(int cant);
    int getMinasVecinas() const;
private:
    bool mina;
    bool revelada;
    bool bandera;
    int minasVecinas;
};

#endif // CELDA_H
