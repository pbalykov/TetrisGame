#ifndef TETRIS_DATA_HPP
#define TETRIS_DATA_HPP

#include "figure.hpp"
#include "field.hpp"

struct TetrisData {
    const Field& map;
    const Figure& figureMain;
    int dropFigureMainY;
    const Figure& figureSecond;
    bool isEndGame; // [TODO] enum { type game pause, game, wing, EndGame
    int level;
    int score;
};

#endif
