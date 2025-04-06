//
// Created by Thomas on 2025/4/6.
//

#ifndef FLAGZOMBIE_HPP
#define FLAGZOMBIE_HPP
#include "Zombie.hpp"

class Flagzombie : public Zombie {
public:
    Flagzombie();
    void Setbacktomove() override;
    void SetDead() override;
    void SetEat() override;
};
#endif //FLAGZOMBIE_HPP
