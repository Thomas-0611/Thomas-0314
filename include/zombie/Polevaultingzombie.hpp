//
// Created by Thomas on 2025/4/8.
//

#ifndef POLEVAULTINGZOMBIE_HPP
#define POLEVAULTINGZOMBIE_HPP

#include "Zombie.hpp"

class Polevaultingzombie : public Zombie {
public:
    Polevaultingzombie();
    void Update(GameContext& ctx) override;
    void Setbacktomove() override;
    void SetDead() override;
    void SetEat() override;
    void SetJump();
    bool GetJump() {
        return jumping;
    }
private:
    bool firsttouch = false;
    bool jumping = false;
};
#endif //POLEVAULTINGZOMBIE_HPP
