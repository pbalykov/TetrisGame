#include "../headers/field.hpp"

#include <algorithm>
#include <iostream> //Дебаг удолить

Field::Field() : _arr(Field::HEIGHT, 
                    std::vector<Color>(Field::WIDTH, Color::NONE)){}


bool Field::isNone(int x, int y) const {
    if ( x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT )
        return false;
    return _arr[y][x] == Color::NONE;
}

Color Field::getColorCell(int x, int y) const {
    if ( x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT )
        return Color::NONE;
    return _arr[y][x];
}

short Field::delRow() {
   int scoreDel = 0;
    for (int i = 0; i < HEIGHT; i++) {
        auto tmp = std::find(_arr[i].begin(), _arr[i].end(), Color::NONE);
        if ( tmp == _arr[i].end() ) {
            _arr.erase(_arr.begin() + i);
            _arr.insert(_arr.begin(), std::vector<Color>(Field::WIDTH));
            scoreDel++;
        }
    }
    return scoreDel;
}

void Field::installFigure(const Figure& figure) {
    auto arr = figure.getArr();
    auto color = figure.getColor();
    for (int i = 0; i < arr.size(); i++) {
        int x = arr[i].first;
        int y = arr[i].second;
        _arr[y][x] = color;
    }
}

const std::vector<std::vector<Color> >& Field::getArr() const {
    return _arr;
}

bool Field::isInstall(const Figure& figure) const {
     auto arr = figure.getArr();
     for (int i = 0; i < arr.size(); i++) 
         if ( isNone(arr[i].first, arr[i].second) ) return false;
     return true;
}
