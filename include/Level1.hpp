//
// Created by tommy on 2025/5/1.
//

#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include "Level.hpp"

class Level1:public Level {
public:
    Level1() = default;
    void Load(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants) override {
        ZombieSpawner spawner(root, zombies);
        if (!m_stage) {
            m_stage = std::make_shared<BackgroundImage>();
            m_stage->SetBackgroundImage("one");
            m_stage->SetZIndex(-9);
            root.AddChild(m_stage);
        } else {
            m_stage->SetBackgroundImage("one");
            m_stage->SetZIndex(-9);
        }

        int storeplantCount = 1; // 可以調整植物生成數量
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            storeplants.push_back(storeplant);
            root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     3, 520, 100, 3 });
    }

    void GameUpdate(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(root, zombies);
        if (!finalWaveSpawned && AllZombiesDead(zombies)) {
            // spawner.Spawn({ ZombieSpawner::Type::Buckethead, 1, 520, 0, 3 });
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 3 });
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,0,3});
            finalWaveSpawned = true;
        }
    }

    bool AllZombiesDead(const std::vector<std::shared_ptr<Zombie>>& zombies) {
        for (const auto& zombie : zombies) {
            if (!zombie->GetDead()) {
                return false;
            }
        }
        return true;
    }

private:
    bool finalWaveSpawned = false;

};

#endif //LEVEL1_HPP
