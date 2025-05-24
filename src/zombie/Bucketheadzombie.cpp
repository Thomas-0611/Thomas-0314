//
// Created by Thomas on 2025/4/6.
//
#include "zombie/Bucketheadzombie.hpp"

Bucketheadzombie::Bucketheadzombie() : Zombie(){
    std::vector<std::string> bucketheadzombieImages;
    for (int i = 0; i < 15; ++i) {
        bucketheadzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/BucketheadZombie(walk)/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(bucketheadzombieImages);
    SetZIndex(2);
    SetPosition({620, 15});
    SetVisible(true);
    Setlife(3000);
    SetAttackfreq(180);
    SetAttackvalue(200);
}
void Bucketheadzombie::SetEat(){
    if (!GetDead()) {
        std::vector<std::string> bucketheadzombieeatImages;
        for (int i = 0; i < 11; ++i) {
            bucketheadzombieeatImages.emplace_back(RESOURCE_DIR"/Day/Zombie/BucketheadZombie(eat)/frame_" + std::to_string(i) + "_delay-0.09s.png");
        }
        SetAnimation(bucketheadzombieeatImages);
        Seteatvalue(true);
    }
}

void Bucketheadzombie::Setbacktomove(){
    std::vector<std::string> bucketheadzombieImages;
    for (int i = 0; i < 15; ++i) {
        bucketheadzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/BucketheadZombie(walk)/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(bucketheadzombieImages);
    Seteatvalue(false);
    Setcurfreq(0);
    Set_m_targetnull();
}

void Bucketheadzombie::SetDead(){
    if (!GetDead()) {
        Set_m_dead(true);
        std::vector<std::string> bucketheadzombiedeadImages;
        for (int i = 0; i < 10; ++i) {
            bucketheadzombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(bucketheadzombiedeadImages);
        SetLooping(false);
        SetPlaying(true);
    }
}