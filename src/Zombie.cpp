//
// Created by Thomas on 2025/3/20.
//
#include "zombie/Zombie.hpp"

Zombie::Zombie()
    : AnimatedCharacter(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> zombieImages;
    for (int i = 0; i < 18; ++i) {
        zombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(walk)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }
    SetAnimation(zombieImages);
    SetZIndex(2);
    SetPosition({620, 15});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(3);
    SetAttackvalue(200);
}

void Zombie::Update() {
    if (!m_dead) {
        SetLooping(true);
        SetPlaying(true);
        auto cur_pos = GetPosition();
        SetPosition({cur_pos[0] - 0.15, cur_pos[1]});

        if (Getlife() <= 0 ) {
            SetDead();
        }
    }
}

void Zombie::SetDead() {
    if (!m_dead) {
        m_dead = true;
        std::vector<std::string> zombiedeadImages;
        for (int i = 0; i < 10; ++i) {
            zombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(zombiedeadImages);
        SetLooping(false);
        SetPlaying(true);
    }
}
