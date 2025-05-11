//
// Created by tommy on 2025/5/1.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "Level.hpp"
#include "Level1.hpp"
#include "Level2.hpp"
// #include "Level2.hpp"  // 新增新關卡

class LevelManager {
public:
    void LoadLevel(int levelId, Util::Renderer& root, std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants) {
        m_levelId = levelId;
        switch (m_levelId) {
            case 1:
                level = std::make_shared<Level1>();
                break;
            case 2:
                level = std::make_shared<Level2>();
                break;
            default:
                break;
        }
        level->Load(root, zombies, storeplants);
    }

    void Update(Util::Renderer& root, std::vector<std::shared_ptr<Zombie>>& zombies) {
        level->GameUpdate(root, zombies);
    }
    std::shared_ptr<Level> Getcurrentlevel() {
        return level;
    }
    void Setlevlenull() {
        level = nullptr;
    }
private:
    std::shared_ptr<Level> level;
    int m_levelId;
};

#endif //LEVELMANAGER_HPP
