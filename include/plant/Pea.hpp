//
// Created by Thomas on 2025/3/21.
//

#ifndef PEA_HPP
#define PEA_HPP

#include "AnimatedCharacter.hpp"
#include <vector>

class Pea : public AnimatedCharacter {
public:
    Pea(const std::vector<std::string>& peaAnimationPaths, float startX, float startY);
    void Update(); // 每幀更新豌豆的位置

    bool IsOutOfBounds() const; // 檢查豌豆是否超出視窗

private:
    float m_speed = 5.0f;  // 豌豆移動的速度
};

#endif //PEA_HPP
