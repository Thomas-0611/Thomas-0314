//
// Created by Thomas on 2025/4/6.
//

#ifndef BUCKETHEADZOMBIE_HPP
#define BUCKETHEADZOMBIE_HPP

#include "Zombie.hpp"

class Bucketheadzombie : public Zombie {
public:
    Bucketheadzombie();
    void Setbacktomove() override;
    void SetDead() override;
    void SetEat() override;
};

#endif //BUCKETHEADZOMBIE_HPP
