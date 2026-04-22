//
// Created by ailem on 11/4/2026.
//

#include "EquipoLaboratorio.h"

EquipoLaboratorio::EquipoLaboratorio(const string& id, double criticidad, double estado, const string& tipoEquipo, bool calibrado) : Equipo(id, criticidad, estado), tipoEquipo(tipoEquipo), calibrado(calibrado) { }

void EquipoLaboratorio::degradar() {
    double factorDegradacion = (!calibrado) ? 2.5 : 1.5;
    estado -= factorDegradacion;
    if (estado < 0.0) estado = 0.0;
    incrementarTiempoInactivo();
}

void EquipoLaboratorio::aplicarMantenimiento(){
    estado += 40.0;
    if (estado > 100.0) estado = 100.0;
    calibrado = true;
    resetearInactivo();
}

string EquipoLaboratorio::getTipo() const { return "Equipo de Laboratorio"; }

string EquipoLaboratorio::getTipoEquipo() const { return tipoEquipo; }

bool EquipoLaboratorio::isCalibrado() const { return calibrado; }

void EquipoLaboratorio::setCalibrado(bool c) { calibrado = c; }