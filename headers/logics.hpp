#ifndef LOGICS_HPP
#define LOGICS_HPP

#include "field.hpp"
#include "figure.hpp"

class Logics {
public:
    using MOVE = Figure::TYPE_MOVE;

    Logics();
    void step();   
    void move(MOVE value);

    const Figure& getFirstFigure() const;
    const Figure& getSecondFigure() const;
    const Field& getMap() const;
    int getScore() const;

    bool endGame() const;


private:
    Field _map;

    Figure _figure1;
    Figure _figure2;

    int _score; //количто 
    bool _endGame; //конец игры
                   //
    int _scoreLavel;
                   
};


#endif
