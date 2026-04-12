//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_EXCEPCIONES_H
#define SISTEMAPIM_EXCEPCIONES_H
#include <exception>
#include <string>

using namespace std;

class ArchivoInvalidoException : public exception{
private:
    string mensaje;
public:
    ArchivoInvalidoException(const string& msg);
    const char* what() const noexcept override;
};

class FormatoInvalidoException : public exception{
private:
    string mensaje;
public:
    FormatoInvalidoException(const string& msg);
    const char* what() const noexcept override;
};

class OperacionInconsistenteException : public exception{
private:
    string mensaje;
public:
    OperacionInconsistenteException(const string& msg);
    const char* what() const noexcept override;
};


#endif //SISTEMAPIM_EXCEPCIONES_H