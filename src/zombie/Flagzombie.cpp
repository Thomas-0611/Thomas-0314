//
// Created by Thomas on 2025/4/6.
//
#include "zombie/Flagzombie.hpp"

Flagzombie::Flagzombie() : Zombie(){
    std::vector<std::string> flagzombieImages;
    for (int i = 0; i < 12; ++i) {
        flagzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/FlagZombie(walk)/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(flagzombieImages);
    SetZIndex(2);
    SetPosition({620, 15});
    SetVisible(true);
    Setlife(1600);
    SetAttackfreq(180);
    SetAttackvalue(200);
}
void Flagzombie::SetEat(){
    if (!GetDead()) {
        std::vector<std::string> flagzombieeatImages;
        for (int i = 0; i < 11; ++i) {
            flagzombieeatImages.emplace_back(RESOURCE_DIR"/Day/Zombie/FlagZombie(eat)/frame_" + std::to_string(i) + "_delay-0.09s.png");
        }
        SetAnimation(flagzombieeatImages);
        Seteatvalue(true);
    }
}

void Flagzombie::Setbacktomove(){
    std::vector<std::string> flagzombieImages;
    for (int i = 0; i < 12; ++i) {
        flagzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/FlagZombie(walk)/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(flagzombieImages);
    Seteatvalue(false);
    Setcurfreq(0);
    Set_m_targetnull();
}

void Flagzombie::SetDead(){
    if (!GetDead()) {
        Set_m_dead(true);
        std::vector<std::string> flagzombiedeadImages;
        for (int i = 0; i < 10; ++i) {
            flagzombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(flagzombiedeadImages);
        SetLooping(false);
        SetPlaying(true);
    }
}