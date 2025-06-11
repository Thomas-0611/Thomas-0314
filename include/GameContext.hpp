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
#include "BackgroundImage.hpp"

#include "plant/Plant.hpp"
#include "plant/Snowpea.hpp"
class Lawnmower;

struct GameContext {
    Util::Renderer& m_Root;
    std::vector<std::shared_ptr<Zombie>>& zombies;
    std::vector<std::shared_ptr<Sun>>& suns;
    std::vector<std::shared_ptr<Pea>>& peas;
    std::vector<std::shared_ptr<Snowpea>>& snowpeas;
    std::vector<std::shared_ptr<Plant>>& plants;
    std::vector<std::shared_ptr<BackgroundImage>>& storeplants;
    std::vector<Plant*> to_remove_plants; // 延遲移除名單
    std::vector<std::shared_ptr<Button>>& grid_buttons;
    std::vector<std::shared_ptr<Lawnmower>>& lawnmowers;
    float grid_x;
    float grid_y;
    int& button_number;
};

#endif //GAMECONTEXT_HPP
