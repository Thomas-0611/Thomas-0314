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

private:
    bool m_dead = false;
};

#endif //ZOMBIE_HPP
