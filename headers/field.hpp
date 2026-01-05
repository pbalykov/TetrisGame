#ifndef FIELD_HPP
#define FIELD_HPP

#include "commonEnum.hpp"
#include "figure.hpp"

#include <vector>

class Figure;

class Field {
public:
    static constexpr short WIDTH = 10;
    static constexpr short HEIGHT = 20;

    Field();
    
    bool isNone(int x, int y) const;
    bool isInstall(const Figure& figure) const;
    
    Color getColorCell(int x, int y) const;

    short delRow();

    void installFigure(const Figure& figure);

    const std::vector<std::vector<Color> >& getArr() const;

private:
    std::vector<std::vector<Color> > _arr;
};

#endif
