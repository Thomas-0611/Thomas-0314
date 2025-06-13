//
// Created by Thomas on 2025/6/13.
//

#ifndef ISHOOTER_HPP
#define ISHOOTER_HPP

#include "GameContext.hpp"
#pragma once

class IShooter {
public:
    virtual void Shoot(GameContext& ctx) = 0;
    virtual ~IShooter() = default;
};

#endif //ISHOOTER_HPP
