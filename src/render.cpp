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

bool Render::Game(const TetrisData& value) {
    auto size = getWindowSize();
    if ( WINDOW_WIDTH > size.first || WINDOW_HEIGHT > size.second )
        return false;

    int begin_x = size.first / 2 - Field::HEIGHT / 2; //заменить на перменные множаем на два так как слишеом тесно
    int begin_y = size.second / 2 - (Field::WIDTH * 2) / 2; //заменить на перменные
    
    _draw_table(begin_x, begin_y, Field::HEIGHT, Field::WIDTH * 2);
    mvprintw(begin_y - 1, size.first / 2 - NAME_FOLDER.size() / 2,
            "%s", NAME_FOLDER);
    move(begin_y, begin_x);
 
    for (int i = 0; i < Field::HEIGHT; i++) { 
        for (int j = 0; j < Field::WIDTH; j++) {
            auto color = value.map.getColorCell(j, i);
            _color.setColorGame(color);
            printw(color == Color::NONE ? CELL_EMPTY : CELL_FILLED);
            _color.setColorGame(Color::NONE);
        }
        move(begin_y + i + 1, begin_x);
    }
    auto arrFigure = value.figureMain.getArr();

    _color.setColorGame(value.figureMain.getColor(), ColorRender::FillType::TEXT);
    for (const auto &i : arrFigure ) 
        mvprintw(begin_y + i.second + value.dropFigureMainY, begin_x + i.first * 2, CELL_DROP);

    _color.setColorGame(value.figureMain.getColor());
    for (const auto &i : arrFigure ) 
        mvprintw(begin_y + i.second, begin_x + i.first * 2, CELL_FILLED);
    _color.setColorGame(Color::NONE);

    begin_x += 21 + 2;
    _draw_table(begin_x, begin_y, FOLDER_NEXT_HEIGHT, 4);
    mvprintw(begin_y - 1, begin_x + (FOLDER_NEXT_HEIGHT / 2 - NAME_NEXT.size() / 2), "%s", NAME_NEXT.data());
    auto arrFigureSecond = value.figureSecond.getArr();
    _color.setColorGame(value.figureSecond.getColor());
    
    auto maxXfigure = std::max_element(arrFigureSecond.begin(), arrFigureSecond.end(), 
                        [](const auto& a, const auto& b) {
                            return a.first < b.first;
                        })->first * 2;

    int beginTmpX = FOLDER_NEXT_HEIGHT / 2 - maxXfigure / 2 - 1;
    for (const auto &i : arrFigureSecond ) {
        mvprintw(begin_y + i.second + 1, begin_x + beginTmpX + i.first * 2, CELL_FILLED);
    }
    _color.setColorGame(Color::NONE); 

    begin_x -= 21 + 2 + 15 + 4;
    _draw_table(begin_x, begin_y, 
            FOLDER_STATUS_WIDTH, FOLDER_STATUS_HEIGHT);
    mvprintw(begin_y - 1, begin_x + (FOLDER_STATUS_WIDTH / 2 - NAME_FOLDER.size() / 2), NAME_STATUS.data());
    mvprintw(begin_y, begin_x + 1, "Score  % 7d", value.score);
    mvprintw(begin_y + 2, begin_x + 1, "Level  % 7d", value.level);


    refresh();

    return true;
}
