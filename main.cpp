#include <iostream>
#include "Simulador.h"
#include "CargadorDatos.h"
#include "Excepciones.h"
#include "Utiles.h"

using namespace std;

int main() {
    InterfazConsola* interfaz = new InterfazConsola();
    interfaz->ejecutar();
    delete interfaz;

    return 0;
}