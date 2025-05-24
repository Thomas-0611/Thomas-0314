//
// Created by Thomas on 2025/4/6.
//
#include "zombie/Coneheadzombie.hpp"

Coneheadzombie::Coneheadzombie() : Zombie(){
    std::vector<std::string> coneheadzombieImages;
    for (int i = 0; i < 21; ++i) {
        coneheadzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/ConeheadZombie(walk)/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(coneheadzombieImages);
    SetZIndex(2);
    SetPosition({620, 15});
    SetVisible(true);
    Setlife(2000);
    SetAttackfreq(180);
    SetAttackvalue(200);
}
void Coneheadzombie::SetEat(){
    if (!GetDead()) {
        std::vector<std::string> coneheadzombieeatImages;
        for (int i = 0; i < 11; ++i) {
            coneheadzombieeatImages.emplace_back(RESOURCE_DIR"/Day/Zombie/ConeheadZombie(eat)/frame_" + std::to_string(i) + "_delay-0.09s.png");
        }
        SetAnimation(coneheadzombieeatImages);
        Seteatvalue(true);
    }
}

void Coneheadzombie::Setbacktomove(){
    std::vector<std::string> coneheadzombieImages;
    for (int i = 0; i < 21; ++i) {
        coneheadzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/ConeheadZombie(walk)/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(coneheadzombieImages);
    Seteatvalue(false);
    Setcurfreq(0);
    Set_m_targetnull();
}

void Coneheadzombie::SetDead(){
    if (!GetDead()) {
        Set_m_dead(true);
        std::vector<std::string> coneheadzombiedeadImages;
        for (int i = 0; i < 10; ++i) {
            coneheadzombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(coneheadzombiedeadImages);
        SetLooping(false);
        SetPlaying(true);
    }
}