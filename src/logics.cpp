#include "../headers/logics.hpp"

#include <utility>
#include <chrono>

Logics::Logics() : _score(0), _endGame(false) {
    _figure1.centerX(Field::WIDTH);
    _complexity.resetTimer();
}

bool Logics::endGame() const {
    return _endGame;
}

void Logics::stepFigure() {
    if ( _endGame ||  _complexity.shouldPerformFall() ) return;

    bool moveSuccess = _figure1.step(_map);
    _complexity.resetTimer();
    if ( moveSuccess ) return;
    
    _map.installFigure(_figure1);
    int tmpScore = _map.delRow();
    if (_score / 10 != (tmpScore + _score) / 10 )
        _complexity.increaseLevel();
    _score += tmpScore;
        
    
    _figure1 = _figure2;
    _figure2 = Figure();
    _figure1.centerX(Field::WIDTH);
    _endGame = _map.isInstall(_figure1);
}

void Logics::shiftFigure(MOVE value) {
    if ( _endGame ) return;
    _figure1.shift(_map, value);
}

void Logics::hardDropFigure() {
    if ( _endGame ) return;
    while ( _figure1.step(_map) );
    _complexity.scheduleImmediateFall();
}

void Logics::softDropFigure() { 
    if ( _endGame ) return;
    _complexity.scheduleImmediateFall();
}

void Logics::reversalFigure() {
    if ( _endGame ) return;
    _figure1.reversal(_map);
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

int Logics::getCurrentLevel() const {
    return _complexity.getCurrentLevel();
}
