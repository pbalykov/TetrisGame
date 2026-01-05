#include "../headers/logics.hpp"

#include <utility>

#include <iostream>

Logics::Logics() : _score(0), _endGame(false), _scoreLavel(0) {
    _figure1.centerX(Field::WIDTH);
}

bool Logics::endGame() const {
    return _endGame;
}

void Logics::step() {
    if ( _endGame || _figure1.step(_map) ) return;
    
    _map.installFigure(_figure1);
    _score += _map.delRow() + 1;
    
    _figure1 = _figure2;
    _figure2 = Figure();
    _figure1.centerX(Field::WIDTH);
    _endGame = _map.isInstall(_figure1);
}

void Logics::move(MOVE value) {
    if ( _endGame ) return;
    _figure1.move(_map, value);
}

const Figure& Logics::getFirstFigure() const {
    return _figure1;
}

const Figure& Logics::getSecondFigure() const {
    return _figure2;
}
    
const Field& Logics::getMap() const {
    return _map;
}

int Logics::getScore() const {
    return _score;
}


