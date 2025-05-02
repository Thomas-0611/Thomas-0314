//
// Created by tommy on 2025/5/1.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "Level1.hpp"
// #include "Level2.hpp"  // 新增新關卡

class LevelManager {
public:
    static void LoadLevel(int levelId, Util::Renderer& root, std::vector<std::shared_ptr<Zombie>>& zombies) {
        switch (levelId) {
            case 1:
                Level1::Load(root, zombies);
                break;
            // case 2:
            //     Level2::Load(root);
            //     break;
            default:
                break;
        }
    }
};

#endif //LEVELMANAGER_HPP
