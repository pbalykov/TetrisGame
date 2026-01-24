#include "../headers/colorRender.hpp"

#include <ncurses.h>

ColorRender::ColorRender() :
    _colorCurrent(Color::NONE), _type(FillType::BACKGROUND)  {

    start_color();
    use_default_colors(); 
    init_pair(static_cast<int>(Color::VIOLET), -1, COLOR_VIOLET_CASTOM);
    init_pair(static_cast<int>(Color::ORANGE), -1, COLOR_ORANGE_CASTOM);
    init_pair(static_cast<int>(Color::CYAN), -1, COLOR_CYAN);
    init_pair(static_cast<int>(Color::YELLOW), -1, COLOR_YELLOW);
    init_pair(static_cast<int>(Color::PURPLE), -1, COLOR_MAGENTA); 
    init_pair(static_cast<int>(Color::GREEN), -1, COLOR_GREEN);
    init_pair(static_cast<int>(Color::RED), -1, COLOR_RED);
    init_pair(static_cast<int>(Color::BLUE), -1, COLOR_BLUE);
    init_pair(static_cast<int>(Color::NONE), -1, -1);

    auto text = static_cast<int>(FillType::TEXT);
    init_pair(static_cast<int>(Color::VIOLET) + text, COLOR_VIOLET_CASTOM, -1);
    init_pair(static_cast<int>(Color::ORANGE) + text, COLOR_ORANGE_CASTOM, -1);
    init_pair(static_cast<int>(Color::CYAN) + text, COLOR_CYAN, -1);
    init_pair(static_cast<int>(Color::YELLOW) + text, COLOR_YELLOW, -1);
    init_pair(static_cast<int>(Color::PURPLE) + text, COLOR_MAGENTA, -1); 
    init_pair(static_cast<int>(Color::GREEN) + text, COLOR_GREEN, -1);
    init_pair(static_cast<int>(Color::RED) + text, COLOR_RED, -1);
    init_pair(static_cast<int>(Color::BLUE) + text, COLOR_BLUE, -1);
}

Color ColorRender::getColor() const {
    return _colorCurrent;
}

void ColorRender::setColorGame(Color value, FillType type) {
    attroff(COLOR_PAIR(static_cast<int>(_colorCurrent) + static_cast<int>(_type)));
    attron(COLOR_PAIR(static_cast<int>(value) + static_cast<int>(type)));
    _colorCurrent = value;
    _type = type;
}
