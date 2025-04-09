//
// Created by Thomas on 2025/4/5.
//
//
// Created by Thomas on 2025/4/4.
//
#include "plant/Wallnut.hpp"
#include "zombie/Zombie.hpp"

Wallnut::Wallnut()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> WallnutImages;
    for (int i = 0; i < 16; ++i) {
        WallnutImages.emplace_back(RESOURCE_DIR"/Day/Plant/Wallnut/frame_" + std::to_string(i) + "_delay-0.09s.png");
    }
    SetAnimation(WallnutImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(3000);
    SetAttackfreq(600);
    SetAttackvalue(0);
}

void Wallnut::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);
    }
    else {
        SetDead();
    }
}