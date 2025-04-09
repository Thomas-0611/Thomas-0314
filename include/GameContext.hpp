//
// Created by Thomas on 2025/4/4.
//

#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#pragma once

#include "Util/Renderer.hpp"
#include "plant/Sun.hpp"
#include "plant/Pea.hpp"
#include "zombie/Zombie.hpp"
#include <vector>
#include <memory>

struct GameContext {
    Util::Renderer& m_Root;
    std::vector<std::shared_ptr<Zombie>>& zombies;
    std::vector<std::shared_ptr<Sun>>& suns;
    std::vector<std::shared_ptr<Pea>>& peas;
};

#endif //GAMECONTEXT_HPP
