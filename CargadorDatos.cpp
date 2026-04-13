//
// Created by antho on 12/4/2026.
//

#include "CargadorDatos.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include <fstream>
#include <sstream>
using namespace std;

Severidad CargadorDatos::parsearSeveridad(const string& s) {
    if (s == "BAJA")    return Severidad::Baja;
    if (s == "MEDIA")   return Severidad::Media;
    if (s == "ALTA")    return Severidad::Alta;
    if (s == "CRITICA") return Severidad::Critica;
    throw FormatoInvalidoException("Severidad desconocida: " + s);
}

void CargadorDatos::cargarDesdeArchivo(const string& nombreArchivo,
                                        vector<Equipo*>& equipos,
                                        vector<Incidencia*>& incidencias) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw ArchivoInvalidoException("No se pudo abrir el archivo: " + nombreArchivo);
    }

    string linea;
    int numLinea = 0;
    while (getline(archivo, linea)) {
        numLinea++;
        if (linea.empty()) continue;

        stringstream ss(linea);
        vector<string> partes;
        string parte;
        while (getline(ss, parte, ';')) {
            partes.push_back(parte);
        }

        if (partes[0] == "INC") {
            if (partes.size() < 4) {
                throw FormatoInvalidoException("Linea " + to_string(numLinea) + ": incidencia incompleta");
            }
            string id = "INC-" + partes[1] + "-" + partes[3];
            string equipoID = partes[1];
            Severidad sev = parsearSeveridad(partes[2]);
            int dia = stoi(partes[3]);
            incidencias.push_back(new Incidencia(id, equipoID, sev, dia));

        } else if (partes.size() >= 6 && partes[1] == "computo") {
            string id = partes[0];
            double criticidad = stod(partes[2]);
            double estado = stod(partes[3]);
            int ram = stoi(partes[4]);
            string so = partes[5];
            equipos.push_back(new EquipoComputo(id, criticidad, estado, ram, so));

        } else if (partes.size() >= 6 && partes[1] == "laboratorio") {
            string id = partes[0];
            double criticidad = stod(partes[2]);
            double estado = stod(partes[3]);
            string tipoEquipo = partes[4];
            bool calibrado = (partes[5] == "true");
            equipos.push_back(new EquipoLaboratorio(id, criticidad, estado, tipoEquipo, calibrado));

        } else {
            throw FormatoInvalidoException("Linea " + to_string(numLinea) + ": formato desconocido");
        }
    }
    archivo.close();
}