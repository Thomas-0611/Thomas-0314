//
// Created by Thomas on 2025/3/20.
//

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "AnimatedCharacter.hpp"
#include <memory>
#include <vector>

#include "Util/Renderer.hpp"

class Plant; // 👈 Forward declaration

class Zombie : public AnimatedCharacter {
public:
    Zombie();
    void Update(Util::Renderer& m_Root,std::vector<std::shared_ptr<Plant>> &plants);
    bool GetDead() const { return m_dead; }
    void SetDead();
    void Seteatvalue(bool value) {
        eating = value;
    }
    bool GetEating() const {
        return eating;
    }
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    void SetEat();
    void Setbacktomove();
    std::array<float, 2> GetSize() const override { return {110.0f, 144.0f}; }
private:
    std::shared_ptr<Plant> m_targetPlant = nullptr;
    int cur_freq = 0;
    bool m_dead = false;
    bool eating = false;
};

#endif //ZOMBIE_HPP
