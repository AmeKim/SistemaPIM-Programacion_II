//
// Created by ailem on 9/4/2026.
//

#include "Equipo.h"
#include "Incidencia.h"
#include "Excepciones.h"

Equipo::Equipo(const string id, double criticidad, double estado) : id(id), criticidad(criticidad), estado(estado), tiempoInactivo(0) {}

double Equipo::calcularPrioridad() const {
    return (criticidad * 0.5)
        +  (contarIncidenciasActivas() * 0.3 )
        +  (tiempoInactivo * 0.2 );
}

void Equipo::resolverIncidencias(){
    for (int i = 0; i < incidencias.size(); i++) {
        incidencias[i]->resolver();
    }
}

void Equipo::agregarIncidencia(Incidencia* inc) {
    if (inc == nullptr) {
        throw OperacionInconsistenteException("Incidencia nula no permitida");
    }
    incidencias.push_back(inc);
}

int Equipo::contarIncidenciasActivas() const {
    int count = 0;
    for (int i = 0; i < incidencias.size(); i++) {
        if (incidencias[i]->esActiva()) count++;
    }
    return count;
}

string Equipo::getId() const { return id; }
double Equipo::getCriticidad() const { return criticidad; }
double Equipo::getEstado() const { return estado; }
int Equipo::getTiempoInactivo() const { return tiempoInactivo; }

void Equipo::setEstado(double e) { estado = e; }
void Equipo::incrementarTiempoInactivo(){ tiempoInactivo++; }
void Equipo::resetearInactivo(){ tiempoInactivo = 0; }
