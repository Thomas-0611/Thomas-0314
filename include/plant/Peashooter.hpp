//
// Created by Thomas on 2025/3/21.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "AnimatedCharacter.hpp"
#include "plant/Pea.hpp"
#include <vector>
#include "Util/Renderer.hpp"
#include "zombie/Zombie.hpp"

class Peashooter : public AnimatedCharacter {
public:
    Peashooter();
    Util::Renderer Update(Util::Renderer m_Root,std::vector<std::shared_ptr<Zombie>>& zombies);
    bool GetDead() const { return m_dead; }
    void SetDead();
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    std::vector<std::shared_ptr<Pea>> GetPeas() {
        return peas;
    }
private:
    bool m_dead = false;
    int cur_freq = 0;
    std::vector<std::shared_ptr<Pea>> peas;  // 儲存射出的豌豆
};

#endif //PEASHOOTER_HPP
