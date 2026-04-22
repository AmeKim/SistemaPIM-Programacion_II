//
// Created by ailem on 9/4/2026.
//

#include "EquipoComputo.h"

EquipoComputo::EquipoComputo(const string& id, double criticidad, double estado, int ramGB, const string& SO) : Equipo(id, criticidad, estado), ramGB(ramGB), sistemaOperativo(SO) { }

void EquipoComputo::degradar() {
    double factorDegradacion = (ramGB <= 4) ? 2.0 : 1.0;
    estado -= factorDegradacion;
    if (estado < 0) estado = 0.0;
    incrementarTiempoInactivo();
}

void EquipoComputo::aplicarMantenimiento(){
    estado += 35.0;
    if (estado > 100.0) estado = 100.0;
    resetearInactivo();
}

string EquipoComputo::getTipo() const { return "Equipo de Computo"; }

int EquipoComputo::getRamGB() const { return ramGB; }

string EquipoComputo::getSistemaOperativo() const { return sistemaOperativo; }
