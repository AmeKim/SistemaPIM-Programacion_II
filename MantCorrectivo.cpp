//
// Created by ailem on 11/4/2026.
//

#include "MantCorrectivo.h"
#include "Utiles.h"
#include "Incidencia.h"

void MantCorrectivo::ejecutar(Equipo& e){
    e.aplicarMantenimiento();
    e.resolverIncidencias();
}

string MantCorrectivo::getNombre() const { return "Mantenimiento Correctivo";}