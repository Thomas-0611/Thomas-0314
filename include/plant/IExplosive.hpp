//
// Created by Thomas on 2025/6/8.
//

#ifndef IEXPLOSIVE_HPP
#define IEXPLOSIVE_HPP

#pragma once

#include "GameContext.hpp"

class IExplosive {
public:
    virtual ~IExplosive() = default;

    // 爆炸範圍攻擊殭屍的方法，傳入 GameContext
    virtual void Explode(GameContext& ctx) = 0;
};
#endif //IEXPLOSIVE_HPP
