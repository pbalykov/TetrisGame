#ifndef COLOR_RENDER_HPP
#define COLOR_RENDER_HPP

#include "commonEnum.hpp"

class ColorRender {
public:
    ColorRender();
    Color getColor() const;
    void setColorGame(const Color value);
private:
    Color _colorCurrent;
};

#endif
