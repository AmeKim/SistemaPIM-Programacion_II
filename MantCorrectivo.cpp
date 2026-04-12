//
// Created by ailem on 11/4/2026.
//

#include "MantCorrectivo.h"
#include "Utiles.h"
#include "Incidencia.h"

void MantCorrectivo::ejecutar(Equipo& e){
    e.aplicarMantenimiento();
    e.resolverIncidencias();
    Utiles::print("[Correctivo] Reparacion urgente aplicada a:" + e.getId() + "\n");
}

string MantCorrectivo::getNombre() const { return "Mantenimiento Correctivo";}