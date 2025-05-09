//
// Created by tommy on 2025/5/8.
//

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "ZombieSpawner.hpp"

class Level {
public:
    Level() = default;
    virtual void Load(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants) = 0;
    virtual void GameUpdate(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies) = 0;
};

#endif //LEVEL_HPP
