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
    virtual void Update(Util::Renderer& m_Root,std::vector<std::shared_ptr<Plant>> &plants);
    bool GetDead() const { return m_dead; }
    virtual void SetDead();
    void Seteatvalue(bool value) {
        eating = value;
    }
    bool GetEating() const {
        return eating;
    }
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    int Getcurfreq() const {
        return cur_freq;
    }
    void Set_m_targetnull() {
        m_targetPlant = nullptr;
    }
    void Set_targetplant(std::shared_ptr<Plant> plant) {
        m_targetPlant = plant;
    }
    std::shared_ptr<Plant> GetTargetPlant() const {
        return m_targetPlant;
    }
    void Set_m_dead(bool value) {
        m_dead = value;
    }
    void Set_snowpea_shooted(int value) {
        snowpea_shooted = value;
    }
    int Get_snowpea_shooted() const {
        return snowpea_shooted;
    }
    void Add_snowpea_freq(int value) {
        snowpea_freq += value;
    }
    int Get_snowpea_freq() const {
        return snowpea_freq;
    }
    void Setstartcount(bool value) {
        startcount = value;
    }
    bool Getstartcount() const {
        return startcount;
    }
    void Addfrozenfreq(int value) {
        frozen_freq += value;
    }
    int Getfrozenfreq() const {
        return frozen_freq;
    }
    virtual  void SetEat();
    virtual void Setbacktomove();
    std::array<float, 2> GetSize() const override { return {110.0f, 144.0f}; }
private:
    std::shared_ptr<Plant> m_targetPlant = nullptr;
    int cur_freq = 0;
    bool m_dead = false;
    bool eating = false;
    int snowpea_shooted = 0;
    int snowpea_freq = 0;
    int frozen_freq = 0;
    bool startcount = false;
};

#endif //ZOMBIE_HPP
