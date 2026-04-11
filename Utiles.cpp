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

void Utiles::limpiar() { system("cls"); }

void Utiles::limpiarEnter() {
    print("\nPresione ENTER para continuar\n");
    cin.get();
    system("cls");
}