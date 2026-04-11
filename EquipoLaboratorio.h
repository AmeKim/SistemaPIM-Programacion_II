//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_EQUIPOLABORATORIO_H
#define SISTEMAPIM_EQUIPOLABORATORIO_H

#include <string>
#include "Equipo.h"

using namespace std;

class EquipoLaboratorio : public Equipo {
private:
    string tipoEquipo;
    bool calibrado;

public:
    EquipoLaboratorio(const string& id, double criticidad, double estado, const string& tipoEquipo, bool calibrado);

    void degradar() override;
    void aplicarMantenimiento() override;
    string getTipo() const override;

    string getTipoEquipo() const;
    bool isCalibrado() const;

    void setCalibrado(bool c);
};


#endif //SISTEMAPIM_EQUIPOLABORATORIO_H