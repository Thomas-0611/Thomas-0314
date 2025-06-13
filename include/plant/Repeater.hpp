//
// Created by Thomas on 2025/4/5.
//

#ifndef REPEATER_HPP
#define REPEATER_HPP

#include "AnimatedCharacter.hpp"
#include "plant/Plant.hpp"
#include "plant/Pea.hpp"
#include <vector>
#include "plant/IShooter.hpp"


class Repeater : public Plant, public IShooter {
public:
    Repeater();
    void Update(GameContext& ctx) override;
    void Shoot(GameContext &ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    void Addnum() {
        num += 1;
    }
    int Getnum() {
        return num%2;
    }
    std::array<float, 2> GetSize() const override { return {71.0f, 71.0f}; }
    std::vector<std::shared_ptr<Pea>> GetPeas() {
        return peas;
    }
private:
    int cur_freq = 0;
    int num = 0; // 是不是第一顆
    std::vector<std::shared_ptr<Pea>> peas;  // 儲存射出的豌豆
};
#endif //REPEATER_HPP
