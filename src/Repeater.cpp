//
// Created by Thomas on 2025/4/5.
//
#include "plant/Repeater.hpp"

Repeater::Repeater()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> repeaterImages;
    for (int i = 0; i < 15; ++i) {
        repeaterImages.emplace_back(RESOURCE_DIR"/Day/Plant/Repeater/frame_" + std::to_string(i) + "_delay-0.09s.png");
    }
    SetAnimation(repeaterImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(1800);
    SetAttackfreq(180);
    SetAttackvalue(200);
}

void Repeater::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);

        int freq = GetAttackfreq();
        if (cur_freq >= freq) {
            //TODO:射出豌豆
            Shoot(ctx);
        }
        else {
            Setcurfreq(cur_freq+1);
        }
    }
    else {
        SetDead();
    }
}

void Repeater::Shoot(GameContext& ctx) {
    std::vector<std::string> peaImages;
    peaImages.emplace_back(RESOURCE_DIR"/Day/Plant/pea/pea.png");

    auto pea = std::make_shared<Pea>(peaImages, GetPosition()[0], GetPosition()[1]);
    ctx.peas.push_back(pea);
    ctx.m_Root.AddChild(pea);

    Addnum(); // 雙發邏輯
    if (Getnum() == 1) {
        Setcurfreq(cur_freq - 10);
    } else {
        Setcurfreq(0);
    }
}