//
// Created by Thomas on 2025/4/10.
//

#ifndef SNOWPEA_HPP
#define SNOWPEA_HPP

#include "AnimatedCharacter.hpp"
#include <vector>

class Snowpea : public AnimatedCharacter {
public:
    Snowpea(const std::vector<std::string>& peaAnimationPaths, float startX, float startY);
    void Update(); // 每幀更新豌豆的位置
    std::array<float, 2> GetSize() const override { return {30.0f, 30.0f}; }
    bool IsOutOfBounds() const; // 檢查豌豆是否超出視窗

private:
    float m_speed = 4.0f;  // 豌豆移動的速度

};

#endif //SNOWPEA_HPP
