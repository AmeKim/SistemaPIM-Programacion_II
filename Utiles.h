//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_UTILES_H
#define SISTEMAPIM_UTILES_H
#include <string>
#include <iomanip>

using namespace std;

class Utiles{
public:
    static void print(string valor);
    static void print(int valor);
    static void print(double valor);

    static string digPalabra();
    static int digNum();
    static double digDouble();

    static string formatear(double valor, int decimales = 2);
    static void imprimirSeparador();
    static void imprimirEncabezadoEquipos();
    static void imprimirEncabezadoMantemiento();

    static void limpiar();
    static void limpiarEnter();
};

#endif //SISTEMAPIM_UTILES_H