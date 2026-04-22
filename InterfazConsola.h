//
// Created by ailem on 21/4/2026.
//

#ifndef SISTEMAPIM_INTERFAZCONSOLA_H
#define SISTEMAPIM_INTERFAZCONSOLA_H
#include <vector>
#include <string>
#include "Equipo.h"
#include "Utiles.h"
using namespace std;

class InterfazConsola{
public:
    void mostrarIniciSimulacion();
    void mostrarDia(int dia);
    void mostrarTopPrioridad(const vector<Equipo*>& equipos, int limite);
    void mostrarEncabezadoMantenimiento();
    void mostrarFilaMantenimiento(Equipo* equipo, const string& tipoMant);
    void mostrarDetalleEquipo(Equipo* equipo);
    void mostrarResumenDia(int backlog, double riesgoGlobal, const string& nivelRiesgo);
    void mostrarSimulacionCompletada(double riesgoGlobal, const string& nivelRiesgo);
};

#endif //SISTEMAPIM_INTERFAZCONSOLA_H
