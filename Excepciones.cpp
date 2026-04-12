//
// Created by ailem on 11/4/2026.
//

#include "Excepciones.h"

ArchivoInvalidoException::ArchivoInvalidoException(const string& msg) : mensaje("Archivo Invalido: " + msg) {}

const char* ArchivoInvalidoException::what() const noexcept{
    return mensaje.c_str();
}

FormatoInvalidoException::FormatoInvalidoException(const string& msg) : mensaje("Formato Invalido: " + msg) {}

const char* FormatoInvalidoException::what() const noexcept{
    return mensaje.c_str();
}

OperacionInconsistenteException::OperacionInconsistenteException(const string& msg) : mensaje("Opeacion Inconsistente: " + msg) {}

const char* OperacionInconsistenteException::what() const noexcept{
    return mensaje.c_str();
}