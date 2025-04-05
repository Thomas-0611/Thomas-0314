//
// Created by Thomas on 2025/4/5.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP

#include "AnimatedCharacter.hpp"
#include "plant/Plant.hpp"


class Wallnut : public Plant {
public:
    Wallnut();
    void Update(GameContext& ctx) override;
    std::array<float, 2> GetSize() const override { return {71.0f, 71.0f}; }
// private:
//     int cur_freq = 0;

};

#endif //WALLNUT_HPP
