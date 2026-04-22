//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_SIMULADOR_H
#define SISTEMAPIM_SIMULADOR_H

#include <string>
#include <vector>
#include <random>
#include "Equipo.h"
#include "Incidencia.h"
#include "IMantenimiento.h"
#include "MantPreventivo.h"
#include "MantCorrectivo.h"
#include "Excepciones.h"
#include "Reporte.h"
#include "InterfazConsola.h"

class Simulador{
private:
    vector<Equipo*> equipos;
    vector<Incidencia*> incidencias;
    int diaActual;
    int backlog;
    double riesgoGlobal;
    mt19937 generador;
    Reporte* reporte;
    InterfazConsola* interfaz;

    void mergeSort(vector<Equipo*>& vec, int inicio, int fin);
    void merge(vector<Equipo*>& vec, int inicio, int mid, int fin);

    Equipo* buscarEquipoPorID(const string& id);

    void generarIncidencias();

    void calcularRiesgoGlobal();

    IMantenimiento* seleccionarEstrategia(Equipo* equipo);

public:
    Simulador();
    ~Simulador();

    void agregarEquipo(Equipo* equipo);
    void ejecutarSimulacion();
    void ejecutarDia();

    vector<Equipo*> getEquipos();
    int getDiaActual() const;
    int getBacklog() const;
    double getRiesgoGlobal() const;
    string nivelRiesgo() const;
};


#endif //SISTEMAPIM_SIMULADOR_H