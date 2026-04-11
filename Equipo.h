//
// Created by ailem on 9/4/2026.
//

#ifndef SISTEMAPIM_EQUIPO_H
#define SISTEMAPIM_EQUIPO_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Incidencia; //forward declaration

class Equipo{
protected:
    string id;
    double criticidad;
    double estado;
    int tiempoInactivo;
    vector<Incidencia*> incidencias;

public:
    Equipo(const string id, double criticidad, float estado);
    virtual ~Equipo() = default;

    double calcularPrioridad() const;

    void agregarIncidencia(Incidencia* inc);
    int contarIncidenciasActivas() const;

    virtual void degradar() = 0;
    virtual void aplicarMantenimiento() =0;
    virtual string getTipo() const = 0;

    string getId() const;
    double getCriticidad() const;
    double getEstado() const;
    int getTiempoInactivo() const;

    void setEstado();
    void incrementarTiempoInactivo();
    void resetearInactivo();

};


#endif //SISTEMAPIM_EQUIPO_H