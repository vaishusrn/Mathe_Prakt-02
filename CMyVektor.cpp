#include "CMyVektor.h"

CMyVektor::CMyVektor()
    {
        dimension = 0;
    }
   CMyVektor:: CMyVektor(int dim)
    {
        dimension = dim; 
        werte.resize(dim); 
    }
    
    void CMyVektor:: setDimension(int dim)
    {
        dimension = dim;
        werte.resize(dim);
    }
    int CMyVektor:: getDimension() const
    {
        return dimension;
    }
    void CMyVektor:: setKomponente(int index, double wert)
    {
        if (index >= 0 && index < dimension)
        {
            werte[index] = wert;
        }
    }
    double CMyVektor:: getKomponente(int index)
    {
        if (index >= 0 && index < dimension)
        {
            return werte[index];
        }
        else
        {
            return 0.0; // Alternativ: throw oder Fehlermeldung
        }
    }
    double &CMyVektor::operator[](int index)
    {
        return werte.at(index);
    }

    const double &CMyVektor::operator[](int index) const
    {
        return werte.at(index);
    }

    double CMyVektor::laenge() const
    {
        double summe = 0.0;
        for (int i = 0; i < dimension; ++i)
        {
            summe += werte[i] * werte[i];
        }
        return sqrt(summe);
    }

    void CMyVektor:: ausgabe() const
    {
        cout << "(";
        for (int i = 0; i < dimension; ++i)
        {
            cout << werte[i];
            if (i < dimension - 1)
                cout << ",";
        }
        cout << ")" << endl;
    }
CMyVektor operator+(const CMyVektor a, const CMyVektor b)
{
    if (a.getDimension() != b.getDimension())
    {
        return CMyVektor();
    }
    CMyVektor result(a.getDimension());
    for (int i = 0; i < a.getDimension(); ++i)
    {
        result[i] = a[i] + b[i];
    }
    return result;
}
CMyVektor operator*(double lamda, const CMyVektor a)
{
    CMyVektor result(a.getDimension());
    for (int i = 0; i < a.getDimension(); ++i)
    {
        result[i] = lamda * a[i];
    }
    return result;
}
