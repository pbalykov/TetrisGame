#include "../headers/render.hpp"
#include <ncurses.h>
#include <unistd.h>

namespace {
    void repeat(int value_char, int size) {
        for (int i = 0; i < size; i++)
            addch(value_char);
    }
    
    void draw_border(int x, int y, int width, int height) {
        move(y - 1, x - 1);
        addch(ACS_ULCORNER);
        repeat(ACS_HLINE, width);
        addch(ACS_URCORNER);
        for (int i = 0; i < height; i++) {
            move(y + i, x - 1);
            addch(ACS_VLINE);
            printw("%*c", width, ' ');
            move(y + i, x + width);
            addch(ACS_VLINE);
        }
        move(y + height, x - 1);
        addch(ACS_LLCORNER);
        repeat(ACS_HLINE, width);
        addch(ACS_LRCORNER);
        move(y + height, x + width);
    }
}

int Render::_maxString(const std::string_view* value) const {
    int maxString = 0;
    for (int i = 0; i < std::size(MENU); i++) {
        if (MENU[i].size() > maxString) {
            maxString = MENU[i].size();
        }
    }
    return maxString;
}

void Render::_draw_table(int begin_x, int begin_y, int width, int height) const {
    draw_border(begin_x, begin_y, width, height);
}

Render::Render() {
    noecho();
}

Render::~Render() {
    echo();
}

std::pair<int, int> Render::getWindowSize() {
    int x, y;
    getmaxyx(stdscr, y, x);
    return std::pair<int, int>(x, y);
}

void Render::draw_centered_text(int y, int center_x, const std::string_view& text) {
    mvprintw(y, center_x - text.size() / 2, "%s", text.data());
}

void Render::draw_menu_items(int begin_x, int begin_y, int maxStringMenu) {
    for (int i = 1; i < std::size(MENU); i++) {
        draw_centered_text(begin_y + i, begin_x + maxStringMenu / 2, MENU[i]);
    }
}

bool Render::drawMenu(int cursor) {
    auto size = getWindowSize();
    if (WINDOW_WIDTH > size.first || WINDOW_HEIGHT > size.second)
        return false;

    int maxStringMenu = _maxString(MENU);
    int begin_x = size.first / 2 - maxStringMenu / 2;
    int begin_y = size.second / 2 - std::size(MENU) / 2;
    
    _draw_table(begin_x, begin_y, maxStringMenu, std::size(MENU));
    draw_centered_text(begin_y - TABLE_BORDER_OFFSET, size.first / 2, MENU[0]);
    draw_menu_items(begin_x, begin_y, maxStringMenu);
    
    refresh();
    return true;
}

void Render::draw_game_field(int begin_x, int begin_y, const TetrisData& value) {
    int field_width_chars = Field::WIDTH * CELL_WIDTH;
    int field_height_chars = Field::HEIGHT;
    
    _draw_table(begin_x, begin_y, field_width_chars, field_height_chars);
    draw_centered_text(begin_y - TABLE_BORDER_OFFSET, begin_x + field_width_chars / 2, NAME_FOLDER);
    
    for (int y = 0; y < Field::HEIGHT; y++) {
        move(begin_y + y, begin_x);
        for (int x = 0; x < Field::WIDTH; x++) {
            auto color = value.map.getColorCell(x, y);
            _color.setColorGame(color);
            printw(color == Color::NONE ? CELL_EMPTY : CELL_FILLED);
            _color.setColorGame(Color::NONE);
        }
    }
}

void Render::draw_current_figure(int begin_x, int begin_y, const TetrisData& value) {
    auto arrFigure = value.figureMain.getArr();
    
    _color.setColorGame(value.figureMain.getColor(), ColorRender::FillType::TEXT);
    for (const auto &cell : arrFigure) {
        mvprintw(begin_y + cell.second + value.dropFigureMainY, 
                 begin_x + cell.first * CELL_WIDTH, 
                 CELL_DROP);
    }
    
    _color.setColorGame(value.figureMain.getColor());
    for (const auto &cell : arrFigure) {
        mvprintw(begin_y + cell.second, 
                 begin_x + cell.first * CELL_WIDTH, 
                 CELL_FILLED);
    }
    _color.setColorGame(Color::NONE);
}

void Render::draw_next_figure_panel(int begin_x, int begin_y, const TetrisData& value) {
    _draw_table(begin_x, begin_y, FOLDER_NEXT_HEIGHT, NEXT_PANEL_HEIGHT);
    draw_centered_text(begin_y - TABLE_BORDER_OFFSET, 
                       begin_x + FOLDER_NEXT_HEIGHT / 2, 
                       NAME_NEXT);
    
    auto arrFigureSecond = value.figureSecond.getArr();
    _color.setColorGame(value.figureSecond.getColor());
    
    int maxXfigure = value.figureSecond.getWidthFigure() * CELL_WIDTH;
    int figure_start_x = FOLDER_NEXT_HEIGHT / 2 - maxXfigure / 2 - 1;
    
    for (const auto &cell : arrFigureSecond) {
        mvprintw(begin_y + cell.second + NEXT_FIGURE_OFFSET, 
                 begin_x + figure_start_x + cell.first * CELL_WIDTH, 
                 CELL_FILLED);
    }
    _color.setColorGame(Color::NONE);
}

void Render::draw_status_panel(int begin_x, int begin_y, const TetrisData& value) {
    _draw_table(begin_x, begin_y, FOLDER_STATUS_WIDTH, FOLDER_STATUS_HEIGHT);
    draw_centered_text(begin_y - TABLE_BORDER_OFFSET, 
                       begin_x + FOLDER_STATUS_WIDTH / 2, 
                       NAME_STATUS);
    
    mvprintw(begin_y, begin_x + STATUS_INFO_OFFSET, TEXT_SCORE, value.score);
    mvprintw(begin_y + 2, begin_x + STATUS_INFO_OFFSET, TEXT_LEVEL, value.level);
}

bool Render::Game(const TetrisData& value) {
    auto size = getWindowSize();
    if (WINDOW_WIDTH > size.first || WINDOW_HEIGHT > size.second)
        return false;

    int field_width_chars = Field::WIDTH * CELL_WIDTH;
    int field_height_chars = Field::HEIGHT;
    
    int field_begin_x = size.first / 2 - field_width_chars / 2;
    int field_begin_y = size.second / 2 - field_height_chars / 2;
    
    draw_game_field(field_begin_x, field_begin_y, value);
    draw_current_figure(field_begin_x, field_begin_y, value);
    
    int next_panel_x = field_begin_x + field_width_chars + GAME_PANEL_SPACING;
    draw_next_figure_panel(next_panel_x, field_begin_y, value);
    
    int status_panel_x = field_begin_x - FOLDER_STATUS_WIDTH - GAME_PANEL_SPACING;
    draw_status_panel(status_panel_x, field_begin_y, value);
    
    refresh();
    return true;
}
