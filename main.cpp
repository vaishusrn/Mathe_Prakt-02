#include "CMyVektor.h"
#include <iostream>
#include <cmath>
using namespace std;
class CMyMatrix 
{
private:
int row;
int column; 
vector<vector<double>> werte;
public: 
CMyMatrix () {
    row = 0;
    column = 0;
    
}
CMyMatrix ( int m, int n) {
setDimension(m, n);
}
void setDimension(int m, int n){
row = m;
column = n;
werte.resize(m,vector<double>(n,0.0));
}
void setEntry(int i, int j, double wert)
{
    if(i>= 0 && i< row && j>= 0 && j< column)
    werte[i][j] = wert;
}
double getEntry(int i, int j) const
{
    if(i>= 0 && i< row && j>= 0 && j< column)
    return werte[i][j];
    else
    return 0.0;
}
void ausgabe () const 
{
    for (int i = 0; i < row; ++i)
    {
        cout << " ";
        for (int j = 0; j< column; ++j){
        cout << werte[i][j];
        if (j < column -1 ) cout << "; ";
        }
        cout << endl;
    }
}
CMyMatrix invers() const {
    if (row != 2 || column != 2) {
        cout << "nicht 2x2 Matrizen" << endl;
        return CMyMatrix (0, 0);
    }
    double a = werte[0][0], b = werte[0][1], c = werte[1][0], d= werte[1][1];
    double deteminante = a*d - b*c;
    if (deteminante == 0){
        cout << "kein inverse möglich"<< endl;
        return CMyMatrix(0,0);
    }
CMyMatrix result(2, 2);
result.setEntry(0, 0,d / deteminante);
result.setEntry(0, 1, -b/ deteminante);
result.setEntry(1, 0, -c / deteminante);
result.setEntry(1, 1, a / deteminante);
return result;
}
int anzahlrow() const {
    return row;
}
int anzahlcolumn() const {
    return column;
}
}; 
CMyVektor operator*(CMyMatrix A, CMyVektor x){
    int rows = A.anzahlrow();
    int column = A.anzahlcolumn();
    if (column != x.getDimension()) {
        return CMyVektor(0);
    }
    CMyVektor result ( rows);
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < column; j++){
            sum += A.getEntry(i,j) * x.getKomponente(j);
        }
        result.setKomponente (i, sum);
    }
    return result;
}
CMyMatrix jacobi (CMyVektor x, CMyVektor (*funktion) (CMyVektor x)){
    double h = 1e-4;
    int m = x.getDimension(); // Spaltenzahl
    CMyVektor fx = funktion(x);
    int n = fx.getDimension(); // Zeilen 

    CMyMatrix J(n,m);

    for (int j = 0; j< m; j++){
        CMyVektor x_neu = x;
        x_neu.setKomponente(j, x.getKomponente(j) + h); // 1 schritt in der funktion
        CMyVektor f_neu = funktion(x_neu);
        for (int i = 0; i < n; ++i) {
            double ableitung = (f_neu.getKomponente(i) -fx.getKomponente(i)) / h;
            J.setEntry (i, j, ableitung);
        }
    
    }
  return J;
} 
void newtonVerfahren(CMyVektor x, CMyVektor (*funktion)(CMyVektor)){
double tolerance = 1e-5;
int maxSteps = 50;
for ( int schritt = 0; schritt < maxSteps; schritt++) {
    cout <<"Schritt "<< schritt << ": "<< endl;
    cout << "x = "; // Startwert
    x.ausgabe();

    CMyVektor fx = funktion(x); // startwert in f(x) berechnen
    cout << "f(x) = "; 
    fx.ausgabe();

    CMyMatrix J = jacobi(x, funktion); // jacobi
    cout << "f'(x) = " << endl << "(";
    J.ausgabe();
     cout << ")" << endl;

    CMyMatrix J_invers = J.invers(); // inverse
    cout << " (f'(x))^(-1) = " << endl << "(";
    J_invers.ausgabe();
    cout << ")" << endl;

    CMyVektor dx = J_invers * fx; // newton schritt
    cout << "dx = ";
    dx.ausgabe();

    double norm_fx =fx.laenge();
    cout << "|| f(x) || = "<< norm_fx << endl;

    if (norm_fx < tolerance ){
        cout << "Ende wegen || f(x) || <1e-5 bei " << endl;
        cout << "x= " ; 
        x.ausgabe();
        cout << " || f(x) || = " << norm_fx << endl;
return;
    }
x = x + (-1 * dx) ; // neu schritt
}
cout << " Abbruch nach 50 Schritten.";
}
/*CMyVektor testF(CMyVektor x){
    CMyVektor result (2);
    result.setKomponente (0, pow(x.getKomponente(0),3 )* pow(x.getKomponente(1), 3) - 2 * x.getKomponente(1));
    result.setKomponente(1, x.getKomponente(0)-2);
    return result;
}*/

CMyVektor f(CMyVektor x) {
    CMyVektor result (3);
    result.setKomponente(0, x.getKomponente(0) * x.getKomponente(1) * exp(x.getKomponente(2)));
    result.setKomponente(1, x.getKomponente(1) * x.getKomponente(2) * x.getKomponente(3));
    result.setKomponente(2,x.getKomponente(3));
    return result;
}
int main() {
  CMyVektor x(4);
  x.setKomponente(0,1);
  x.setKomponente (1,2);
  x.setKomponente (2,0);
  x.setKomponente(3,3);

  CMyMatrix J = jacobi (x, f);
  cout << "Jacobi - Matrix an (1,2,0,3): "<< endl;
  J.ausgabe(); 
/*CMyVektor startwert (2);
startwert.setKomponente(0,1);
startwert.setKomponente(1,1);
newtonVerfahren(startwert, testF);*/

  system("Pause");
  return 0;
}
