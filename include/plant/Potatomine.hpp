//
// Created by Thomas on 2025/4/19.
//

#ifndef POTATOMINE_HPP
#define POTATOMINE_HPP
#include "plant/Plant.hpp"
#include "plant/IExplosive.hpp"

class Potatomine : public Plant, public IExplosive {
public:
    Potatomine();
    void Update(GameContext& ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    void Setreadymode();
    void Explode(GameContext& ctx) override;
    std::array<float, 2> GetSize() const override { return {75.0f, 55.0f}; }

private:
    int cur_freq = 0;
    bool ready = false;
    bool is_triggered = false;
    int exploding_timer = 0;
};
#endif //POTATOMINE_HPP
