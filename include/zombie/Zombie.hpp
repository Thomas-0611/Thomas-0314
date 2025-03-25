//
// Created by Thomas on 2025/3/20.
//

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "AnimatedCharacter.hpp"

class Zombie : public AnimatedCharacter {
public:
    Zombie();
    void Update();
    bool GetDead() const { return m_dead; }
    void SetDead();
    std::array<float, 2> GetSize() const override { return {110.0f, 144.0f}; }
private:
    bool m_dead = false;
};

#endif //ZOMBIE_HPP
