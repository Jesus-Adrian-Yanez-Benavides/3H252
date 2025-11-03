#ifndef DIBUJO_HPP
#define DIBUJO_HPP

#include <vector>
#include <string>
#include <ftxui/screen/color.hpp>

class Dibujo
{
public:
    int x, y;
    std::vector<std::u32string> datos;
    ftxui::Color color;

    // Constructor
    Dibujo(int x, int y, const std::vector<std::u32string>& datos, ftxui::Color color)
        : x(x), y(y), datos(datos), color(color) {}
};

#endif // DIBUJO_HPP