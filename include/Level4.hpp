//
// Created by Thomas on 2025/5/12.
//

#ifndef LEVEL4_HPP
#define LEVEL4_HPP
#include "Level.hpp"

class Level4:public Level {
public:
    Level4() = default;
    void Load(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants) override {
        ZombieSpawner spawner(root, zombies);

        if (!m_stage) {
            m_stage = std::make_shared<BackgroundImage>();
            m_stage->SetBackgroundImage("five");
            m_stage->SetZIndex(-9);

            root.AddChild(m_stage);
        } else {
            m_stage->SetBackgroundImage("five");
            m_stage->SetZIndex(-9);
        }


        int storeplantCount = 4; // 可以調整植物生成數量 要再改成櫻桃炸彈
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            storeplants.push_back(storeplant);
            root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 520, 200, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 670, 200, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 770, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 890, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 990, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1090, 250, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1200, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1200, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1300, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1310, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1450, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1460, 100, 5 });
    }

    void GameUpdate(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(root, zombies);
        if (!finalWaveSpawned && AllZombiesDead(zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 4 });
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,50,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,0,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,600,50,4});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,0,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,620,50,5});
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
#endif //LEVEL4_HPP
