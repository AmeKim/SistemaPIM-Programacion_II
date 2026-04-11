//
// Created by ailem on 9/4/2026.
//

#ifndef SISTEMAPIM_INCIDENCIA_H
#define SISTEMAPIM_INCIDENCIA_H

#include <string>

using namespace std;
class Equipo;

enum class Severidad{
    Baja,
    Media,
    Alta,
    Critica
};


class Incidencia{
private:
    string id;
    Severidad severidad;
    string equipoID;
    int diaReporte;
    bool activa;

public:
    Incidencia(const string& id, const string& equipoID, Severidad severidad, int diaReporte);

    bool esActiva() const;
    void resolver();

    string getID() const;
    string getEquipoID() const;
    Severidad getSeveridad() const;
    int getDiaReporte() const;

    double getPesoSeveridad() const;

    string severidadToString() const;
};


#endif //SISTEMAPIM_INCIDENCIA_H