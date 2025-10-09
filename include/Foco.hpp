#pragma once
#include <EstadoFoco.hpp>

class Foco
{
private:
    EstadoFoco EstadoActual;

public:
    Foco() { EstadoActual=false; }
    ~Foco() {}
    void Encender () {}
    void Apagar () {}
    EstadoFoco MostrarEstado () {}
};
