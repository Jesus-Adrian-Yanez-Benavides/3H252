#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector> 
#include <random> 

#include "Dibujo.hpp"
#include "GestorDibujos.hpp"

using namespace ftxui;
using namespace std;

int main()
{
    auto screen = Screen::Create(
        Dimension::Fixed(80),
        Dimension::Fixed(24));

    const vector<u32string> gato_sigilo1_derecha = {
        U" /`) /,|__/|   ",
        U"(_ __|  o o|   ",
        U"\\  `  (   T )._ ",
        U"/_\\ `/ '--^'",
        U"  \\)))  \\)))   "
    };
    
    const vector<u32string> gato_sigilo2_derecha = {
        U" /`) /,|__/|   ",
        U"(_ __|  o o|   ",
        U"\\  `  (   T )._ ",
        U"/_\\ `/ '--^' ",
        U" \\)))  \\))) "
    };

    const vector<u32string> pajaro_quieto = {
        U"   __ ", U" ( o>", U"\\_//)", U" \\_/)", U" _|_ "
    };
    const vector<u32string> pajaro_vuela1 = {
        U" \\V/ ", U" (o.o)", U"  \\ / "
    };
    const vector<u32string> pajaro_vuela2 = {
        U" \\   / ", U"--(o.o)--", U"         "
    };
    const vector<u32string> vacio = { U" " };

    const vector<u32string> arbol = {
        U"    /\\    ", U"   /  \\   ", U"  /    \\  ",
        U" /______\\ ", U"    ||    ", U"    ||    "
    };
    const u32string pasto_continuo = U"VvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvvvvvVvVvvvVvv";

    GestorDibujos gestor;

    int gato_x_fijo = 10;
    int gato_y = 17; 
    gestor.Agregar(Dibujo(gato_x_fijo, gato_y, gato_sigilo1_derecha, ftxui::Color::White)); 

    int pajaro_x_inicial = 90; 
    int pajaro_y = 17; 
    gestor.Agregar(Dibujo(pajaro_x_inicial, pajaro_y, pajaro_quieto, ftxui::Color::Cyan)); 

    gestor.Agregar(Dibujo(20, 8, arbol, ftxui::Color::Green));      
    gestor.Agregar(Dibujo(45, 8, arbol, ftxui::Color::Green));      
    gestor.Agregar(Dibujo(70, 8, arbol, ftxui::Color::Green));      
    gestor.Agregar(Dibujo(95, 8, arbol, ftxui::Color::Green));      
    
    bool pajaro_huyendo = false; 
    int frame_huida = 0;
    int scroll_speed = 1; 

    int frames_totales = 500; 
    for (int frame = 0; frame < frames_totales; ++frame)
    {
        screen.Clear();

        int offset = frame % pasto_continuo.length(); 
        int fila_pasto = 22; 
        
        for (int x = 0; x < screen.dimx(); ++x) {
            screen.PixelAt(x, fila_pasto).character = pasto_continuo[(x + offset) % pasto_continuo.length()];
            screen.PixelAt(x, fila_pasto).foreground_color = ftxui::Color::GreenLight;
            
            screen.PixelAt(x, fila_pasto + 1).character = pasto_continuo[(x + offset + 5) % pasto_continuo.length()]; 
            screen.PixelAt(x, fila_pasto + 1).foreground_color = ftxui::Color::Green;
        }

        if (!pajaro_huyendo) 
        {
            if ((frame / 8) % 2 == 0) { 
                gestor.dibujos[0].datos = gato_sigilo1_derecha;
            } else {
                gestor.dibujos[0].datos = gato_sigilo2_derecha;
            }
        } else {
            gestor.dibujos[0].datos = gato_sigilo1_derecha; 
        }

        for (size_t i = 2; i < gestor.dibujos.size(); ++i)
        {
            gestor.dibujos[i].x -= scroll_speed;

            if (gestor.dibujos[i].x < -15) 
            {
                gestor.dibujos[i].x = 85 + (rand() % 20); 
            }
        }

        if (!pajaro_huyendo)
        {
            gestor.dibujos[1].x -= scroll_speed;

            if ((gestor.dibujos[1].x) <= (gato_x_fijo + 20)) 
            {
                pajaro_huyendo = true;
                frame_huida = 0; 
            }
        }
        else 
        {
            frame_huida++;
            
            if ((frame_huida / 5) % 2 == 0) {
                gestor.dibujos[1].datos = pajaro_vuela1;
            } else {
                gestor.dibujos[1].datos = pajaro_vuela2;
            }

            gestor.dibujos[1].x += 2; 
            gestor.dibujos[1].y -= 1; 

            if (gestor.dibujos[1].y < 0 || gestor.dibujos[1].x > screen.dimx())
            {
                gestor.dibujos[1].datos = vacio;
            }
        }
        
        gestor.DibujarTodos(screen);

        cout << screen.ToString();
        cout << screen.ResetPosition();
        cout << flush;

        this_thread::sleep_for(chrono::milliseconds(100)); 
    }

    return 0;
}