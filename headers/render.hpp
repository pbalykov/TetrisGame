#ifndef RENDER_HPP
#define RENDER_HPP

#include "figure.hpp"
#include "field.hpp"
#include "colorRender.hpp"

#include "tetrisData.hpp"

#include <string_view>

class Render {
    static constexpr std::string_view MENU[] = {" MENU ",
    "Game", "About the game", "Exit"};

    static constexpr std::string_view NAME_FOLDER = "TETRIS";
    static constexpr std::string_view NAME_NEXT = "Next";
    static constexpr std::string_view NAME_STATUS = "Status";
    static constexpr std::string_view NAME_HELP = "Help";

    static constexpr const char* CELL_EMPTY = " .";
    static constexpr const char* CELL_FILLED = "  ";
    static constexpr const char* CELL_DROP = "||";

    static constexpr unsigned short FOLDER_STATUS_WIDTH = 16;
    static constexpr unsigned short FOLDER_STATUS_HEIGHT = 3;
    static constexpr unsigned short FOLDER_NEXT_HEIGHT = 12;
    static constexpr unsigned short FOLDER_NEXT_WIDTH = 4;


    static constexpr int WINDOW_WIDTH = 10; // ширина Окна Сдел
    static constexpr int WINDOW_HEIGHT = 10; // высота Окна TODO Сдел

public:
    Render();
    ~Render();

    bool drawMainWindow(); // главное окно:v
 
    bool drawMenu(int cursor = 0); // меню 

    bool Game(const TetrisData& value); 
    
    static std::pair<int, int> getWindowSize();

private:
    ColorRender _color;

    void _draw_table(int start_x, int start_y, int width, int height) const;


//    void _draw_table(int begin_x, int begin_y, int width, int height) const;
    int _maxString(const std::string_view* value) const;

};

#endif
