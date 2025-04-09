//
// Created by Thomas on 2025/4/4.
//
#include "plant/Sunflower.hpp"
#include "zombie/Zombie.hpp"

Sunflower::Sunflower()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> SunflowerImages;
    for (int i = 0; i < 13; ++i) {
        SunflowerImages.emplace_back(RESOURCE_DIR"/Day/Plant/Sunflower/frame_" + std::to_string(i) + "_delay-0.11s.png");
    }
    SetAnimation(SunflowerImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(1000);
    SetAttackfreq(600);
    SetAttackvalue(0);
}

void Sunflower::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);
        int freq = GetAttackfreq();
        if (cur_freq >= freq) {
            auto m_sun = std::make_shared<Sun>();
            m_sun->Setstop_y(GetPosition().y-5);
            m_sun->SetPosition({GetPosition().x+50,GetPosition().y+5});
            ctx.suns.push_back(m_sun);
            ctx.m_Root.AddChild(m_sun);
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