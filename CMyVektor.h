#pragma once
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
class CMyVektor
{
private:
    vector<double> werte; // speichert die Komponenten des Vektors
    int dimension;// Anzahl der Dimensionen des Vektors

public:
    CMyVektor();
    
    CMyVektor(int dim);
   
    void setDimension(int dim);

    int getDimension() const;

    void setKomponente(int index, double wert);

    double getKomponente(int index);
   
    double &operator[](int index);

    const double &operator[](int index) const;

    double laenge() const;
 
    void ausgabe() const;
};
CMyVektor operator+(CMyVektor a, CMyVektor b);
CMyVektor operator*(double lambda, CMyVektor a);