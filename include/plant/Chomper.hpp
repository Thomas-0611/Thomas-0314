//
// Created by Thomas on 2025/4/20.
//

#ifndef CHOMPER_HPP
#define CHOMPER_HPP
#include "plant/Plant.hpp"

class Chomper : public Plant {
public:
    Chomper();
    void Update(GameContext& ctx) override;
    void Seteating(GameContext& ctx);
    void Setbacktonormal();
    std::array<float, 2> GetSize() const override { return {75.0f, 55.0f}; }

private:
    std::shared_ptr<Zombie> m_targetzombie = nullptr;
    bool starteat = false;
    bool eating = false;
    int eating_timer = 0;
};
#endif //CHOMPER_HPP
