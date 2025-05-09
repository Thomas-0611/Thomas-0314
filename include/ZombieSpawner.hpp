//
// Created by tommy on 2025/5/1.
//

#ifndef ZOMBIESPAWNER_HPP
#define ZOMBIESPAWNER_HPP

#include <memory>
#include <vector>
#include "zombie/Coneheadzombie.hpp"
#include "zombie/Bucketheadzombie.hpp"
#include "zombie/Flagzombie.hpp"
#include "zombie/Polevaultingzombie.hpp"
#include "zombie/Zombie.hpp"

class ZombieSpawner {
public:
    enum class Type {
        Regular,
        Polevaulter,
        Conehead,
        Buckethead,
        Flag
    };

    struct Config {
        Type    type;
        int     count;
        int     startX;
        int     spacing;
        int     startY;
    };

    ZombieSpawner(Util::Renderer& root, std::vector<std::shared_ptr<Zombie>>& zombies)
        : m_root(root), m_zombies(zombies) {}

    // Generate zombies according to config
    void Spawn(const Config& cfg) {
        for (int i = 0; i < cfg.count; ++i) {
            std::shared_ptr<Zombie> z;
            switch (cfg.type) {
                case Type::Regular:
                    z = std::make_shared<Zombie>();
                break;
                case Type::Polevaulter:
                    z = std::make_shared<Polevaultingzombie>();
                    z->SetPivot({50, 0});
                break;
                case Type::Conehead:
                    z = std::make_shared<Coneheadzombie>();
                break;
                case Type::Buckethead:
                    z = std::make_shared<Bucketheadzombie>();
                break;
                case Type::Flag:
                    z = std::make_shared<Flagzombie>();
                break;
            }
            int y = (cfg.startY-3)*97.4;
            z->SetPosition({ cfg.startX + i * cfg.spacing, y });
            m_zombies.push_back(z);
            m_root.AddChild(z);
        }
    }




private:
    Util::Renderer& m_root;
    std::vector<std::shared_ptr<Zombie>>& m_zombies;
};

#endif //ZOMBIESPAWNER_HPP
