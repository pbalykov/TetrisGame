#include "../headers/colorRender.hpp"

#include <ncurses.h>

ColorRender::ColorRender() : _colorCurrent(Color::NONE) {
    start_color();
    use_default_colors(); 
    init_pair(static_cast<int>(Color::CYAN), -1, COLOR_CYAN);
    init_pair(static_cast<int>(Color::VIOLET), -1, COLOR_MAGENTA);
    init_pair(static_cast<int>(Color::YELLOW), -1, COLOR_YELLOW);
    init_pair(static_cast<int>(Color::PURPLE), -1, COLOR_MAGENTA); 
    init_pair(static_cast<int>(Color::GREEN), -1, COLOR_GREEN);
    init_pair(static_cast<int>(Color::RED), -1, COLOR_RED);
    init_pair(static_cast<int>(Color::BLUE), -1, COLOR_BLUE);
    init_pair(static_cast<int>(Color::ORANGE), -1, COLOR_YELLOW); 
    init_pair(static_cast<int>(Color::NONE), -1, COLOR_WHITE);
}

Color ColorRender::getColor() const {
    return _colorCurrent;
}

void ColorRender::setColorGame(const Color value) {
    if ( value == Color::NONE ) {
        attroff(COLOR_PAIR(static_cast<int>(_colorCurrent)));
    } else {
        attron(COLOR_PAIR(static_cast<int>(value)));
    }
    _colorCurrent = value;
}
