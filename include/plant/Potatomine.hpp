//
// Created by Thomas on 2025/4/19.
//

#ifndef POTATOMINE_HPP
#define POTATOMINE_HPP
#include "plant/Plant.hpp"

class Potatomine : public Plant {
public:
    Potatomine();
    void Update(GameContext& ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    void Setreadymode();
    void Settoexplore(GameContext& ctx);
    std::array<float, 2> GetSize() const override { return {75.0f, 55.0f}; }

private:
    int cur_freq = 0;
    bool ready = false;
};
#endif //POTATOMINE_HPP
