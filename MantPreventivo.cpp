//
// Created by ailem on 11/4/2026.
//

#include "MantPreventivo.h"
#include "Utiles.h"

void MantPreventivo::ejecutar(Equipo& e){
    e.aplicarMantenimiento();
    Utiles::print("[Preventivo] Mantenimiento aplicado a: " + e.getId() + "\n");
}

string MantPreventivo::getNombre() const{ return "Mantenimiento Preventivo"; }
