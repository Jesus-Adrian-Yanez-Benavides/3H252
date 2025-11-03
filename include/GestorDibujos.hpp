#ifndef GESTOR_DIBUJOS_HPP
#define GESTOR_DIBUJOS_HPP

#include <vector>
#include <ftxui/screen/screen.hpp>
#include "Dibujo.hpp"  // Asumiendo que Dibujo.hpp está en la misma carpeta 'include'

class GestorDibujos
{
public:
    // Almacena todos los dibujos
    std::vector<Dibujo> dibujos;

    // Método para añadir un nuevo dibujo al gestor
    void Agregar(const Dibujo& d)
    {
        dibujos.push_back(d);
    }

    // Método para dibujar todos los dibujos en la pantalla
    void DibujarTodos(ftxui::Screen& screen)
    {
        for (const auto& d : dibujos)
        {
            // Recorrer cada línea del dibujo
            for (size_t i = 0; i < d.datos.size(); ++i)
            {
                // Recorrer cada caracter de la línea
                for (size_t j = 0; j < d.datos[i].size(); ++j)
                {
                    int posX = d.x + j;
                    int posY = d.y + i;

                    // Verificar que esté dentro de los límites de la pantalla
                    if (posX >= 0 && posX < screen.dimx() && posY >= 0 && posY < screen.dimy())
                    {
                        screen.PixelAt(posX, posY).character = d.datos[i][j];
                        screen.PixelAt(posX, posY).foreground_color = d.color;
                    }
                }
            }
        }
    }
};

#endif // GESTOR_DIBUJOS_HPP