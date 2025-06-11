//
// Created by tommy on 2025/5/1.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "Level.hpp"
#include "Level1.hpp"
#include "Level10.hpp"
#include "Level2.hpp"
#include "Level3.hpp"
#include "Level4.hpp"
#include "Level5.hpp"
#include "Level6.hpp"
#include "Level7.hpp"
#include "Level8.hpp"
#include "Level9.hpp"
// 新增新關卡

class LevelManager {
public:
    void LoadLevel(int levelId, GameContext& ctx) {
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
            case 8:
                level = std::make_shared<Level8>();
                break;
            case 9:
                level = std::make_shared<Level9>();
                break;
            case 10:
                level = std::make_shared<Level10>();
                break;
            default:
                break;
        }
        level->Load(ctx);
    }

    void Update(GameContext& ctx) {
        level->GameUpdate(ctx);
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
