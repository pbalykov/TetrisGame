#include "../headers/figure.hpp"

#include <algorithm>
#include <cstdlib>
#include <random>

Figure Figure::makeFigure() {
    const std::vector<std::vector<std::pair<int, int> > > shapes = {
        {{0,0}, {1,0}, {2,0}, {3,0}}, // I
        {{1,0}, {2,0}, {1,1}, {2,1}},  // O
        {{0,0}, {1,0}, {2,0}, {1,1}}, // T
        {{0,0}, {1,0}, {1,1}, {2,1}}, // S
        {{0,1}, {1,1}, {1,0}, {2,0}}, // Z
        {{0,0}, {0,1}, {1,1}, {2,1}}, // J
        {{0,1}, {1,1}, {2,1}, {2,0}}  // L
    };
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, shapes.size() - 1);

    int value = distribution(generator);
    return Figure(shapes[value], static_cast<Color>(value + 1));
}
 
Figure::Figure(const std::vector<std::pair<int, int> >& arr, Color color) : 
    _x(0), _y(0), _arr(arr), _color(color) {};

Figure::Figure() {
    *this = makeFigure();
}

void Figure::shift(const Field& value, TYPE_SHIFT type) {
    for (int i = 0; i < _arr.size(); i++) {
        int newX = type == TYPE_SHIFT::LEFT ? _arr[i].first + _x - 1 : _arr[i].first + _x + 1;
        if ( !value.isNone(newX, _arr[i].second  + _y) ) return ;
    }
    type == TYPE_SHIFT::LEFT ? _x-- : _x++;
}

bool Figure::step(const Field& value) {
    for (int i = 0; i < _arr.size(); i++) 
        if ( !value.isNone(_arr[i].first + _x, _arr[i].second + _y + 1) )
            return false;
    _y++;
    return true;
}

void Figure::reversal(const Field& value) {
    std::vector<std::pair<int, int>> new_arr;
    int cx = 1, cy = 1;
    for (const auto& i : _arr) {
        int new_x = cy - i.second + cx;
        int new_y = i.first - cx + cy;
        new_arr.push_back({new_x, new_y});
    }
    for (int i = 0; i < _arr.size(); i++) 
        if ( !value.isNone(new_arr[i].first + _x, new_arr[i].second + _y) )
            return;
    _arr = std::move(new_arr); 
}

void Figure::centerX(int width) { 
    auto maxXfigure = std::max_element(_arr.begin(), _arr.end(), 
                        [](const auto& a, const auto& b) {
                            return a.first < b.first;
                        })->first;

    _x = width / 2 - maxXfigure / 2 - 1;
}


std::vector<std::pair<int, int> > Figure::getArr() const {
    auto res = _arr;
    for (int i = 0; i < res.size(); i++) 
        res[i] = std::make_pair(res[i].first + _x, res[i].second + _y);
    return res;
}

Color Figure::getColor() const {
    return _color;
} 
