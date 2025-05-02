//
// Created by tommy on 2025/5/1.
//

#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include "ZombieSpawner.hpp"

class Level1 {
public:
    static void Load(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies) {
        ZombieSpawner spawner(root, zombies);
        // Level 1: 1 pole-vaulter, 5 regular, then 1 conehead
        spawner.Spawn({ ZombieSpawner::Type::Polevaulter, 1, 520, 0 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     5, 620, 100 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,    1, 1120, 0 });
        spawner.Spawn({ ZombieSpawner::Type::Buckethead,    1, 1220, 0 });
        spawner.Spawn({ ZombieSpawner::Type::Flag,    1, 1320, 0 });
    }
};

#endif //LEVEL1_HPP
