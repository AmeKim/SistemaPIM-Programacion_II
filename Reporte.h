//
// Created by antho on 12/4/2026.
//

#ifndef SISTEMAPIM_REPORTE_H
#define SISTEMAPIM_REPORTE_H
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Equipo.h"
#include "Excepciones.h"

using namespace std;

class Reporte {
private:
    ofstream archivoDiario;
    ofstream archivoAcumulado;
    string nombreDiario;
    string nombreAcumulado;
    string nivelRiesgo(double riesgoGlobal) const;
public:
    Reporte(const string& nombreDiario, const string& nombreAcumulado);
    ~Reporte();
    void abrirArchivos();
    void cerrarArchivos();
    void registrarDia(int dia,
                      const vector<Equipo*>& equipos,
                      int limite,
                      int backlog,
                      double riesgoGlobal);
    void registrarResumenFinal(int totalDias, double riesgoFinal);
};
#endif //SISTEMAPIM_REPORTE_H