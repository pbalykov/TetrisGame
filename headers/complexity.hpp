#ifndef COMPLEXITY_HPP
#define COMPLEXITY_HPP

#include <array>

class Complexity {    
    static constexpr size_t LEN_DELAYS = 31;
    static constexpr std::array<double, LEN_DELAYS> ARR_DELAYS = 
    {  
        0.800, 0.717, 0.633, 0.550, 0.467, 0.383, 0.300,
        0.217, 0.133, 0.100, 0.083, 0.083, 0.083, 0.067, 
        0.067, 0.067, 0.050, 0.050, 0.050, 0.033, 0.033, 
        0.033, 0.033, 0.033, 0.033, 0.033, 0.033, 0.033, 
        0.033, 0.017
    };
    static constexpr double IMMEDIATE_DELAYS = 0.05;

public:
    Complexity();

    int getCurrentLevel() const;      
    void increaseLevel();              
    void resetTimer();                
    bool shouldPerformFall() const;
    void scheduleImmediateFall();

private:
    int _currentLevel;
    double _accumulatedTime; 
    double _currentDelay;
    bool _immediateFall;
};

#endif
