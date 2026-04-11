//
// Created by ailem on 9/4/2026.
//

#ifndef SISTEMAPIM_EQUIPOCOMPUTO_H
#define SISTEMAPIM_EQUIPOCOMPUTO_H
#include "Equipo.h"
#include <string>

using namespace std;


class EquipoComputo : public Equipo {
private:
    int ramGB;
    string sistemaOperativo;

public:
    EquipoComputo(const string& id, double criticidad, double estado, int ramGB, const string& SO);

    void degradar() override;
    void aplicarMantenimiento() override;
    string getTipo() const override;

    int getRamGB() const;
    string getSistemaOperativo() const;
};


#endif //SISTEMAPIM_EQUIPOCOMPUTO_H