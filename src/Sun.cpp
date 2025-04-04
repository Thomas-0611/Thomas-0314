//
// Created by Thomas on 2025/3/30.
//
#include "plant/Sun.hpp"
#include <random>

Sun::Sun(): AnimatedCharacter(std::vector<std::string>()) {
    std::vector<std::string> sunImages;
    for (int i = 0; i < 29; ++i) {
        sunImages.emplace_back(RESOURCE_DIR"/Day/Plant/Sun/frame_" + std::to_string(i) + ".png");
    }
    SetAnimation(sunImages);
    SetZIndex(2);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-435, 285);
    int x_pos = dist(rng);
    std::mt19937 rng2(std::random_device{}());
    std::uniform_int_distribution<int> dist2(-270, 225);
    int stop_y = dist2(rng2);
    Setstop_y(stop_y);
    SetPosition({x_pos, 250});
    SetVisible(true);
    Setlife(1);
    SetAttackfreq(0);
    SetAttackvalue(0);
}

void Sun::Update() {
    if (!m_pick) {
        SetLooping(true);
        SetPlaying(true);
        auto cur_pos = GetPosition();
        Button sun = Button(cur_pos.x-GetSize()[0]/2,cur_pos.x+GetSize()[0]/2,cur_pos.y-GetSize()[1]/2,cur_pos.y+GetSize()[1]/2);
        if (sun.MouseClickDetect()) {
            SetPick();
        }
        if (cur_pos[1] > Getstop_y()) {
            SetPosition({cur_pos[0], cur_pos[1] - 0.15});
        }
    }
}
void Sun::SetPick() {
    m_pick = true;
    SetLooping(false);
    SetPlaying(false);
}
