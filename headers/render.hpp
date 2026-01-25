#ifndef RENDER_HPP
#define RENDER_HPP

#include "colorRender.hpp"
#include "tetrisData.hpp"

#include <string_view>
#include <string>
#include <utility>

class Render {
    static constexpr std::string_view MENU[] = {" MENU ",
    "Game", "About the game", "Exit"};

    static constexpr std::string_view NAME_FOLDER = "TETRIS";
    static constexpr std::string_view NAME_NEXT = "Next";
    static constexpr std::string_view NAME_STATUS = "Status";
    static constexpr std::string_view NAME_HELP = "Help";

    static constexpr const char* TEXT_SCORE = "Score  % 7d";
    static constexpr const char* TEXT_LEVEL = "Level  % 7d";

    static constexpr int CELL_WIDTH = 2;
    static constexpr const char* CELL_EMPTY = " .";
    static constexpr const char* CELL_FILLED = "  ";
    static constexpr const char* CELL_DROP = "||";

    static constexpr unsigned short FOLDER_STATUS_WIDTH = 16;
    static constexpr unsigned short FOLDER_STATUS_HEIGHT = 3;
    static constexpr unsigned short FOLDER_NEXT_HEIGHT = 12;
    static constexpr unsigned short FOLDER_NEXT_WIDTH = 4;

    static constexpr int WINDOW_WIDTH = 80;  
    static constexpr int WINDOW_HEIGHT = 24; 
         
    static constexpr int GAME_PANEL_SPACING = 2; 
    static constexpr int NEXT_PANEL_HEIGHT = 4;   
    static constexpr int TABLE_BORDER_OFFSET = 1;   
    static constexpr int STATUS_INFO_OFFSET = 1;   
    static constexpr int NEXT_FIGURE_OFFSET = 1;  

public:    
    Render();
    ~Render();

    bool drawMainWindow(); 

    bool drawMenu(int cursor = 0); 

    bool Game(const TetrisData& value); 

    static std::pair<int, int> getWindowSize();

private:
    ColorRender _color;

    void _draw_table(int start_x, int start_y, int width, int height) const;
    int _maxString(const std::string_view* value) const;

    void draw_menu_items(int begin_x, int begin_y, int maxStringMenu);
    
    
    void draw_game_field(int begin_x, int begin_y, const TetrisData& value);
    void draw_current_figure(int begin_x, int begin_y, const TetrisData& value);
    void draw_next_figure_panel(int begin_x, int begin_y, const TetrisData& value);
    void draw_status_panel(int begin_x, int begin_y, const TetrisData& value);
    
    void draw_centered_text(int y, int center_x, const std::string_view& text);

};

#endif
