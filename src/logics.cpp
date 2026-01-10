#include "../headers/logics.hpp"

#include <utility>
#include <chrono>

Logics::Logics() : _score(0), _endGame(false), _scoreLavel(0) {
    _figure1.centerX(Field::WIDTH);
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();
    _callStepTime = std::chrono::duration_cast<std::chrono::duration<double>>(time).count();

}

bool Logics::endGame() const {
    return _endGame;
}

void Logics::step() {
    if (_endGame ) return;
    
    auto tmpTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    double _time = std::chrono::duration_cast<std::chrono::duration<double>>(tmpTime).count();

    if ( _time - _callStepTime <= 0.717) return;
    _callStepTime = _time;

    if ( _figure1.step(_map) ) return;
    
    _map.installFigure(_figure1);
    _score += _map.delRow();
    
    _figure1 = _figure2;
    _figure2 = Figure();
    _figure1.centerX(Field::WIDTH);
    _endGame = _map.isInstall(_figure1);
    
    tmpTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    _callStepTime = std::chrono::duration_cast<std::chrono::duration<double>>(tmpTime).count();
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


