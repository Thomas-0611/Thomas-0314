//
// Created by Thomas on 2025/4/10.
//

#ifndef SNOWPEASHOOTER_HPP
#define SNOWPEASHOOTER_HPP


#include "AnimatedCharacter.hpp"
#include "plant/Plant.hpp"
#include "plant/Snowpea.hpp"
#include <vector>
#include "plant/IShooter.hpp"

class Snowpeashooter : public Plant, public IShooter{
public:
    Snowpeashooter();
    void Update(GameContext& ctx) override;
    void Shoot(GameContext &ctx) override;
    void Setcurfreq(int value) {
        cur_freq = value;
    }
    std::array<float, 2> GetSize() const override { return {71.0f, 71.0f}; }
    std::vector<std::shared_ptr<Snowpea>> Getsnowpeas() {
        return snowpeas;
    }
private:
    int cur_freq = 0;
    std::vector<std::shared_ptr<Snowpea>> snowpeas;  // 儲存射出的豌豆
};


#endif //SNOWPEASHOOTER_HPP
