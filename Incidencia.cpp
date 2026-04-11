//
// Created by ailem on 9/4/2026.
//

#include "Incidencia.h"

Incidencia::Incidencia(const string& id, const string& equipoID, Severidad severidad, int diaReporte) : id(id), equipoID(equipoID), severidad(severidad), diaReporte(diaReporte), activa(true) {}

bool Incidencia::esActiva() const { return activa;}
void Incidencia::resolver(){ activa=false; }

string Incidencia::getID() const { return id; }
string Incidencia::getEquipoID() const { return equipoID; }
Severidad Incidencia::getSeveridad() const { return severidad; }
int Incidencia::getDiaReporte() const { return diaReporte; }

double Incidencia::getPesoSeveridad() const {
    switch (severidad) {
        case Severidad::Baja: return 1.0;
        case Severidad::Media: return 2.0;
        case Severidad::Alta: return 3.0;
        case Severidad::Critica: return 4.0;
        default: return 1.0;
    }
}

string Incidencia::severidadToString() const {
    switch (severidad) {
    case Severidad::Baja: return "Baja";
    case Severidad::Media: return "Media";
    case Severidad::Alta: return "Alta";
    case Severidad::Critica: return "Critica";
    default: return "Desconocida";
    }
}