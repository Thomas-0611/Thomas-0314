//
// Created by Thomas on 2025/4/4.
//

#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP

#include "AnimatedCharacter.hpp"
#include "plant/Plant.hpp"

class Sunflower : public Plant {
public:
    Sunflower();
    void Update(GameContext& ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    std::array<float, 2> GetSize() const override { return {71.0f, 71.0f}; }

private:
    int cur_freq = 0;

};

#endif //SUNFLOWER_HPP
