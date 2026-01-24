#ifndef LOGICS_HPP
#define LOGICS_HPP

#include "field.hpp"
#include "figure.hpp"
#include "complexity.hpp"

#include "tetrisData.hpp"

class Logics {
public:
    using MOVE = Figure::TYPE_SHIFT;

    Logics();
    
    void stepFigure();   
    void shiftFigure(MOVE value);
    void hardDropFigure();
    void softDropFigure();
    void reversalFigure();
    
    const Figure& getFirstFigure() const;
    const Figure& getSecondFigure() const;
    const Field& getMap() const;
    int getScore() const;
    bool endGame() const;
    int getCurrentLevel() const;

    TetrisData getTetrisData() const; 


private:
    int _calculateDropDistance() const;
    Field _map;

    Figure _figure1;
    Figure _figure2;

    Complexity _complexity;

    int _score; 
    bool _endGame;                    
};

#endif
