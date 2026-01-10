#include "../headers/interfase.hpp"

#include <ncurses.h> 

#include <unistd.h>
#include <chrono>
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
        _view->Game(_logicsGame->getMap(), _logicsGame->getFirstFigure(), _logicsGame->getScore());
        auto start = std::chrono::high_resolution_clock::now();
        halfdelay(1);
        auto key = getch();
        switch (key) {
            case KEY_LEFT :
                _logicsGame->move(Logics::MOVE::LEFT);
                break;
            case KEY_RIGHT :
                _logicsGame->move(Logics::MOVE::RIGHT);
                break;
            case KEY_UP:
                _logicsGame->move(Logics::MOVE::REVERSAL);
                break;
            case 'q' :
                return 0;
        }
//        auto end = std::chrono::high_resolution_clock::now();
//        double elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count();
//        if ( elapsed < 300 )
//            usleep((300 - elapsed) * 1000);
        _logicsGame->step();
        flushinp();
    }
    return 0;
}
