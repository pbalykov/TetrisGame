#ifndef COLOR_RENDER_HPP
#define COLOR_RENDER_HPP

#include "commonEnum.hpp"

class ColorRender {
    static constexpr short COLOR_VIOLET_CASTOM = 56;
    static constexpr short COLOR_ORANGE_CASTOM = 214; 
public:

    enum class FillType {
        BACKGROUND = 0,
        TEXT = static_cast<int>(Color::COUNT),
    };

    ColorRender();
    Color getColor() const;
    void setColorGame(Color value, FillType type = FillType::BACKGROUND);
private:
    Color _colorCurrent;
    FillType _type;
};

#endif
