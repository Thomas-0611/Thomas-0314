//
// Created by Thomas on 2025/4/6.
//

#ifndef CONEHEADZOMBIE_HPP
#define CONEHEADZOMBIE_HPP
#include "Zombie.hpp"

class Coneheadzombie : public Zombie {
    public:
        Coneheadzombie();
        void Setbacktomove() override;
        void SetDead() override;
        void SetEat() override;
};
#endif //CONEHEADZOMBIE_HPP
