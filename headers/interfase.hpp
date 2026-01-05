#ifndef INTERFASE_HPP
#define INTERFASE_HPP

#include "logics.hpp"
#include "render.hpp"

class Interfase {
public:
    Interfase();
    ~Interfase();

    int run();

private:
    int _game();

    Logics* _logicsGame;
    Render* _view;
};

#endif
