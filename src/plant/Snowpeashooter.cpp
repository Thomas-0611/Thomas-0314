//
// Created by Thomas on 2025/4/10.
//
#include "plant/Snowpeashooter.hpp"

Snowpeashooter::Snowpeashooter()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> SnowpeashooterImages;
    for (int i = 0; i < 15; ++i) {
        SnowpeashooterImages.emplace_back(RESOURCE_DIR"/Day/Plant/Snowpeashooter/frame_" + std::to_string(i) + "_delay-0.09s.png");
    }
    SetAnimation(SnowpeashooterImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(200);
}

void Snowpeashooter::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);

        int freq = GetAttackfreq();
        if (cur_freq >= freq) {
            //TODO:射出豌豆
            Shoot(ctx);
            Setcurfreq(0);
        }
        else {
            Setcurfreq(cur_freq+1);
        }
    }
    else {
        SetDead();
    }
}

void Snowpeashooter::Shoot(GameContext& ctx) {
    std::vector<std::string> peaImages;
    peaImages.emplace_back(RESOURCE_DIR"/Day/Plant/Snowpea/snowpea.png");

    auto pea = std::make_shared<Snowpea>(peaImages, GetPosition()[0], GetPosition()[1]);
    ctx.snowpeas.push_back(pea);
    ctx.m_Root.AddChild(pea);
}