#ifndef RENDER_HPP
#define RENDER_HPP

#include "../headers/figure.hpp"
#include "../headers/field.hpp"
#include "../headers/colorRender.hpp"

#include <string_view>
#include <iostream>

class Render {
    static constexpr std::string_view MENU[] = {" MENU ",
    "Game", "About the game", "Exit"};

    static constexpr std::string_view NAME_FOLDER = "TETRIS";

    static constexpr int WINDOW_WIDTH = 10; // ширина
    static constexpr int WINDOW_HEIGHT = 10; // высота
public:
    Render();
    ~Render();

    bool drawMainWindow(); // главное окно:v
 
    bool drawMenu(int cursor = 0); // меню 
    
    bool Game(const Field& map, const Figure& figure1);

 //   bool drawGame(int score, const Field& map, 
 //       const Figure& figure1, const Figure& figure2); //окно игры
    
    static std::pair<int, int> getWindowSize();

private:
    ColorRender _color;

    void _draw_table(int begin_x, int begin_y, int width, int height) const;
    int _maxString(const std::string_view* value) const;
};

#endif
