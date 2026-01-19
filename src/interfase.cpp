#include "../headers/interfase.hpp"

#include <ncurses.h> 

#include <unistd.h>
#include <cstdlib>

Interfase::Interfase() : _logicsGame(nullptr), _view(nullptr) {
    initscr();
    keypad(stdscr, true);  
    cbreak();
    curs_set(0);
    _view = new Render;
    _logicsGame = new Logics; //может потом вернуть
}


Interfase::~Interfase() {
    delete _logicsGame;
    _logicsGame = nullptr;
    delete _view;
    _view = nullptr;
    endwin();
}

int Interfase::run() {
    return _game();
}


int Interfase::_game() {
    while (true) {
        wclear(stdscr);
        _view->Game(_logicsGame->getMap(), _logicsGame->getFirstFigure(), _logicsGame->getScore(), _logicsGame->getCurrentLevel());
        halfdelay(1);
        auto key = getch();
        switch (key) {
            case KEY_LEFT :
                _logicsGame->shiftFigure(Logics::MOVE::LEFT);
                break;
            case KEY_RIGHT :
                _logicsGame->shiftFigure(Logics::MOVE::RIGHT);
                break;
            case KEY_UP:
                _logicsGame->reversalFigure();
                break;
            case KEY_DOWN:
                _logicsGame->softDropFigure();
                break;
            case ' ':
                _logicsGame->hardDropFigure();
                break;
            case 'q' :
                return 0;
        }
        _logicsGame->stepFigure();
        flushinp();
    }
    return 0;
}
