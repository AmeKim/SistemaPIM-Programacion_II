#include <iostream>
#include "Simulador.h"
#include "CargadorDatos.h"
#include "Excepciones.h"
#include "Utiles.h"

using namespace std;

int main() {
    try {
        vector<Equipo*> equipos;
        vector<Incidencia*> incidencias;

        CargadorDatos::cargarDesdeArchivo("datos.txt", equipos, incidencias);

        Simulador sim;

        for (int i = 0; i < equipos.size(); i++) {
            sim.agregarEquipo(equipos[i]);
        }

        // Asignar incidencias a sus equipos
        for (int i = 0; i < incidencias.size(); i++) {
            for (int j = 0; j < equipos.size(); j++) {
                if (equipos[j]->getId() == incidencias[i]->getEquipoID()) {
                    equipos[j]->agregarIncidencia(incidencias[i]);
                    break;
                }
            }
        }

        sim.ejecutarSimulacion();

    } catch (const ArchivoInvalidoException& e) {
        Utiles::print(string(e.what()) + "\n");
    } catch (const FormatoInvalidoException& e) {
        Utiles::print(string(e.what()) + "\n");
    } catch (const OperacionInconsistenteException& e) {
        Utiles::print(string(e.what()) + "\n");
    } catch (const exception& e) {
        Utiles::print(string("Error inesperado: ") + e.what() + "\n");
    }

    return 0;
}