#include "../headers/complexity.hpp"

#include <chrono>

Complexity::Complexity() : 
    _currentLevel(0), _accumulatedTime(0),
    _currentDelay(ARR_DELAYS[_currentLevel]), _immediateFall(false) {}

int Complexity::getCurrentLevel() const {
    return _currentLevel; 
}

void Complexity::increaseLevel() {
    _currentLevel++;
    _currentDelay = _currentLevel >= LEN_DELAYS ? 
                        ARR_DELAYS[_currentLevel] : _currentDelay;

}

void Complexity::resetTimer() {
    _immediateFall = false;
    auto tmpTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    _accumulatedTime = std::chrono::duration_cast<std::chrono::duration<double>>(tmpTime).count();
}

bool Complexity::shouldPerformFall() const {
    if (_immediateFall ) return false;
    auto tmpTime = std::chrono::high_resolution_clock::now().time_since_epoch();
    double _time = std::chrono::duration_cast<std::chrono::duration<double>>(tmpTime).count();
    return (_time - _accumulatedTime) <= _currentDelay;
}

void Complexity::scheduleImmediateFall() {
    _immediateFall = true;
}
