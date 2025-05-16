//
// Created by tommy on 2025/5/1.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "Level.hpp"
#include "Level1.hpp"
#include "Level2.hpp"
#include "Level3.hpp"
#include "Level4.hpp"
#include "Level5.hpp"
#include "Level6.hpp"
#include "Level7.hpp"
// #include "Level2.hpp"  // 新增新關卡

class LevelManager {
public:
    void LoadLevel(int levelId, Util::Renderer& root, std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants, int& button_number, std::vector<std::shared_ptr<Lawnmower>>& lawnmowers) {
        m_levelId = levelId;
        switch (m_levelId) {
            case 1:
                level = std::make_shared<Level1>();
                break;
            case 2:
                level = std::make_shared<Level2>();
                break;
            case 3:
                level = std::make_shared<Level3>();
                break;
            case 4:
                level = std::make_shared<Level4>();
                break;
            case 5:
                level = std::make_shared<Level5>();
                break;
            case 6:
                level = std::make_shared<Level6>();
                break;
            case 7:
                level = std::make_shared<Level7>();
                break;
            default:
                break;
        }
        level->Load(root, zombies, storeplants, button_number, lawnmowers);
    }

    void Update(Util::Renderer& root, std::vector<std::shared_ptr<Zombie>>& zombies,GameContext& ctx, std::vector<std::shared_ptr<Lawnmower>>& lawnmowers) {
        level->GameUpdate(root, zombies, ctx, lawnmowers);
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
