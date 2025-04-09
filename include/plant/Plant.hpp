//
// Created by Thomas on 2025/4/3.
//

#ifndef PLANT_HPP
#define PLANT_HPP

#pragma once
#include "AnimatedCharacter.hpp"
#include "Util/Renderer.hpp"
#include "zombie/Zombie.hpp"
#include "GameContext.hpp"

class Plant : public AnimatedCharacter {
public:
    using AnimatedCharacter::AnimatedCharacter;
    // virtual void Update(Util::Renderer& renderer, std::vector<std::shared_ptr<Zombie>>& zombies) = 0;
    virtual void Update(GameContext& ctx) = 0;
    bool GetDead() const { return m_dead; }
    void SetDead() {
        if (!m_dead) {
            m_dead = true;
            SetLooping(false);
            SetPlaying(false);
        }
    };
    virtual ~Plant() = default;
private:
    bool m_dead = false;
};

#endif //PLANT_HPP
