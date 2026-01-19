#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "commonEnum.hpp"
#include "field.hpp"

#include <vector>

class Field;

class Figure {
    static constexpr short SCORE_FIGURE = 7; 
public:
    enum class TYPE_SHIFT {
        LEFT,
        RIGHT,
    };

    Figure();

    Figure makeFigure();
    
    void shift(const Field& value, TYPE_SHIFT type);
    bool step(const Field& value);
    void reversal(const Field& value);

    void centerX(int width);
    
    std::vector<std::pair<int, int> > getArr() const;
    Color getColor() const;    

private:
    Figure(const std::vector<std::pair<int, int> >& arr, Color color);
    
    int _x, _y;
    std::vector<std::pair<int, int> > _arr;
    Color _color;
};


#endif
