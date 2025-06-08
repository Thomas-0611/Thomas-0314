//
// Created by Thomas on 2025/4/18.
//

#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP

#include "plant/Plant.hpp"
#include "plant/IExplosive.hpp"

class Cherrybomb : public Plant, public IExplosive {
public:
    Cherrybomb();
    // Util::Renderer& Update(Util::Renderer& m_Root,std::vector<std::shared_ptr<Zombie>>& zombies) override;
    // void Update(Util::Renderer& m_Root,std::vector<std::shared_ptr<Zombie>>& zombies) override;
    void Update(GameContext& ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    void Explode(GameContext& ctx) override;
    std::array<float, 2> GetSize() const override { return {112.0f, 81.0f}; }

private:
    int cur_freq = 0;
};

#endif //CHERRYBOMB_HPP
