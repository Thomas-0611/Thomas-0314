//
// Created by Thomas on 2025/3/21.
//
#include "plant/Peashooter.hpp"

Peashooter::Peashooter()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> peashooterImages;
    for (int i = 0; i < 13; ++i) {
        peashooterImages.emplace_back(RESOURCE_DIR"/Day/Plant/Peashooter/frame_" + std::to_string(i) + "_delay-0.09s.png");
    }
    SetAnimation(peashooterImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(200);
}

void Peashooter::Update(GameContext& ctx) {
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

void Peashooter::Shoot(GameContext& ctx) {
    std::vector<std::string> peaImages;
    peaImages.emplace_back(RESOURCE_DIR"/Day/Plant/pea/pea.png");

    auto pea = std::make_shared<Pea>(peaImages, GetPosition()[0], GetPosition()[1]);
    ctx.peas.push_back(pea);
    ctx.m_Root.AddChild(pea);
}