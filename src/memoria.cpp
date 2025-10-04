#include <iostream>
using namespace std;

class Empleado{
    private: // Nacen de la relacion tiene
    char nombre[10];    //10B
    int edad;           // 4B
    char direccion[255];// 255B
    int telefono;       // 4B

    public: //Nace de la relacion usa
        int LeerEdad(){
            return 0;
        }
}; // ->>

int main(int argc, char const *argv[])
{
    //Enteros
    cout << "Tamaño di int: " << sizeof(int) << endl;
    cout << "Tamaño de long: " << sizeof(long) << endl;

    //Punto flotante
    cout << "Tamaño de float: " << sizeof(float) << endl;
    cout << "Tamaño de double: " << sizeof(double) << endl;

    //Tamaño de Bytes
    cout << "Tamaño de char: " << sizeof(char) << endl;
    cout << "Tamaño de byte: " << sizeof(byte) << endl;
    cout << "Tamaño de bool: " << sizeof(bool) << endl;

    //Puntero
    cout << "Tamaño de puntero: " << sizeof(int*) << endl;

    //Tamaño de tipos no nativos
    Empleado empleados[10]; //<--- 2730B
    cout << "Tamaño Empleado: " << sizeof(Empleado) << endl;
    cout << "Empleados" << empleados[0].LeerEdad() << endl;
    
    int a = 64;
    char b = (char) a;
    cout << b << endl;

    return 0;
}