//
// Created by Thomas on 2025/3/30.
//

#ifndef SUN_HPP
#define SUN_HPP
#include "AnimatedCharacter.hpp"
#include "Button.hpp"

class Sun : public AnimatedCharacter {
public:
    Sun();
    void Update();
    bool GetPick() const { return m_pick; }
    void SetPick();
    void Setstop_y(int value) {
        stop_y = value;
    }
    int Getstop_y() const { return stop_y; }
    std::array<float, 2> GetSize() const override { return {79.0f, 79.0f}; }
private:
    bool m_pick = false;
    int stop_y = 0;
};

#endif //SUN_HPP
