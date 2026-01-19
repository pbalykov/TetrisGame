#include "../headers/render.hpp"

#include <ncurses.h>
#include <unistd.h>

static void repeat(int value_char, int size) {
    for (int i = 0; i < size; i++) 
        addch(value_char);
}

int Render::_maxString(const std::string_view* value) const {
    int maxString = 0;
    for (int i = 0; i < std::size(MENU); i++) 
        maxString = MENU[i].size() > maxString ? MENU[i].size() : maxString;
    return maxString;
}

void Render::_draw_table(int begin_x, int begin_y, int width, int height) const {
    move(begin_y - 1, begin_x - 1);
    addch(ACS_ULCORNER);
    repeat(ACS_HLINE, width);
	addch(ACS_URCORNER);
    for (int i = 0; i < height; i++) {
        move(begin_y + i, begin_x - 1);
	    addch(ACS_VLINE);
        printw("%*c", width, ' ');
        move(begin_y + i, begin_x + width);
	    addch(ACS_VLINE);
    }
    move(begin_y + height, begin_x - 1);
    addch(ACS_LLCORNER);
	repeat(ACS_HLINE, width);
	addch(ACS_LRCORNER);
    move(begin_y + height, begin_x + width);
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

bool Render::drawMenu(int cursor) {
    auto size = getWindowSize();
    if ( WINDOW_WIDTH > size.first || WINDOW_HEIGHT > size.second ) 
        return false;

    auto maxStringMenu = _maxString(MENU);
    int begin_x = size.first / 2 - maxStringMenu / 2;
    int begin_y = size.second / 2 - std::size(MENU) / 2;
    _draw_table(begin_x, begin_y, maxStringMenu, std::size(MENU));
    mvprintw(begin_y - 1, size.first / 2 - MENU[0].size() / 2, "%s", MENU[0]);
    for (int i = 1; i < std::size(MENU); i++) {
        mvprintw(begin_y + i, size.first / 2 - MENU[i].size() / 2, "%s", MENU[i]);
    }
    refresh();
    return true;      
}

bool Render::Game(const Field& map, const Figure& figure, int score, int level) {
    auto size = getWindowSize();
    if ( WINDOW_WIDTH > size.first || WINDOW_HEIGHT > size.second )
        return false;

    int begin_x = size.first / 2 - 20 / 2; //заменить на перменные множаем на два так как слишеом тесно
    int begin_y = size.second / 2 - 20 / 2; //заменить на перменные

    _draw_table(begin_x, begin_y, 20, 20);
    mvprintw(begin_y - 1, size.first / 2 - NAME_FOLDER.size() / 2, "%s", NAME_FOLDER);
    move(begin_y, begin_x);
 
    for (int i = 0; i < 20; i++) { 
        for (int j = 0; j < 10; j++) {
            auto color = map.getColorCell(j, i);
            _color.setColorGame(color);
            printw(color == Color::NONE ? " ." : "  ");
            _color.setColorGame(Color::NONE);
        }
        move(begin_y + i + 1, begin_x);
    }

    auto arrFigure = figure.getArr();
    _color.setColorGame(figure.getColor());
    for (int i = 0; i < arrFigure.size(); i++)
        mvprintw(begin_y + arrFigure[i].second, begin_x + arrFigure[i].first * 2, "  ");
    _color.setColorGame(Color::NONE);

    begin_x += 21 + 2;
 
    _draw_table(begin_x, begin_y, 10, 4);
    mvprintw(begin_y - 1, begin_x + (10 / 2 - std::string("Next").size() / 2), "%s", "Next");

    begin_x -= 21 + 2 + 15 + 4;
    _draw_table(begin_x, begin_y, 
            FOLDER_STATUS_WIDTH, FOLDER_STATUS_HEIGHT);

    mvprintw(begin_y - 1, begin_x + (FOLDER_STATUS_WIDTH / 2 - NAME_FOLDER.size() / 2), NAME_STATUS.data());

    mvprintw(begin_y, begin_x + 1, "Score  % 7d", score);
    mvprintw(begin_y + 2, begin_x + 1, "Level  % 7d", level);


    refresh();
    return true;
}

















