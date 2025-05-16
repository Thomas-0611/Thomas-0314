//
// Created by Thomas on 2025/3/21.
//
#include "plant/Pea.hpp"

Pea::Pea(const std::vector<std::string>& peaAnimationPaths, float startX, float startY)
    : AnimatedCharacter(peaAnimationPaths) {
    SetPosition({startX, startY});
    SetZIndex(2);
    SetVisible(true);
}

void Pea::Update() {
    // 豌豆移動
    auto position = GetPosition();
    SetPosition({position[0] + m_speed, position[1]}); // 豌豆水平向右移動
}

bool Pea::IsOutOfBounds() const {
    auto position = GetPosition();
    return position[0] > 300;  // 假設 800 是視窗的右邊界
}
