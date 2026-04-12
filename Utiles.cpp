#include "Utiles.h"
#include <iostream>
using namespace std;

void Utiles::print(string valor)  { cout << valor; }
void Utiles::print(int valor)     { cout << valor; }
void Utiles::print(double valor)  { cout << valor; }

string Utiles::digPalabra() {
    string valor;
    getline(cin, valor);
    return valor;
}

int Utiles::digNum() {
    int valor;
    if (cin >> valor) {
        cin.ignore();
        return valor;
    } else {
        cin.clear();
        cin.ignore();
        print("Error: Solo se permiten digitos\n");
        return 0;
    }
}

double Utiles::digDouble() {
    double valor;
    if (cin >> valor) {
        cin.ignore();
        return valor;
    } else {
        cin.clear();
        cin.ignore();
        print("Error: Solo se permiten digitos\n");
        return 0;
    }
}

string Utiles::formatear(double valor, int decimales){
    stringstream s;
    s << fixed << setprecision(decimales) << valor;
    return s.str();

}

void Utiles::imprimirSeparador() {
    print("------------ ----------- ---------- -------------------------\n");
}

void Utiles::imprimirEncabezadoEquipos() {
    stringstream ss;
    ss << left
       << setw(14) << "ID"
       << setw(12) << "Prioridad"
       << setw(11) << "Estado"
       << setw(25) << "Tipo" << "\n";
    print(ss.str());
    imprimirSeparador();
}

void Utiles::imprimirEncabezadoMantemiento() {
    stringstream s;
    s << left
       << setw(14) << "ID"
       << setw(25) << "Tipo Mantenimiento"
       << setw(11) << "Estado"
       << setw(12) << "Incidencias" << "\n";
    print(s.str());
    print("------------ ------------------------ ---------- -----------\n");
}

void Utiles::limpiar() { system("cls"); }

void Utiles::limpiarEnter() {
    print("\nPresione ENTER para continuar\n");
    cin.get();
    system("cls");
}