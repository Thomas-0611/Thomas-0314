//
// Created by Thomas on 2025/3/21.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "AnimatedCharacter.hpp"
#include "plant/Plant.hpp"
#include "plant/Pea.hpp"
#include <vector>


class Peashooter : public Plant {
public:
    Peashooter();
    // Util::Renderer& Update(Util::Renderer& m_Root,std::vector<std::shared_ptr<Zombie>>& zombies) override;
    // void Update(Util::Renderer& m_Root,std::vector<std::shared_ptr<Zombie>>& zombies) override;
    void Update(GameContext& ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    std::array<float, 2> GetSize() const override { return {71.0f, 71.0f}; }
    std::vector<std::shared_ptr<Pea>> GetPeas() {
        return peas;
    }
private:
    int cur_freq = 0;
    std::vector<std::shared_ptr<Pea>> peas;  // 儲存射出的豌豆
};

#endif //PEASHOOTER_HPP
