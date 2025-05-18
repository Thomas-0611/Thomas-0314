//
// Created by Thomas on 2025/5/13.
//

#ifndef LEVEL5_HPP
#define LEVEL5_HPP

#include "Level.hpp"

class Level5:public Level {
public:
    Level5() = default;
    void Load(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants, int& button_number, std::vector<std::shared_ptr<Lawnmower>>& lawnmowers) override {
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

        button_number = 5;//輸入1or3or5

        for(int i = 1; i < 6; i++) {
            lawnmower = std::make_shared<Lawnmower>(i);
            lawnmowers.emplace_back(lawnmower);
            root.AddChild(lawnmower);
        }

        int storeplantCount = 5; // 可以調整植物生成數量 要再改成櫻桃炸彈
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            storeplants.push_back(storeplant);
            root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 520, 200, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 520, 200, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 670, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 670, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 820, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 820, 250, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1000, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1000, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1000, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1000, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1120, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1120, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1120, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     2, 1120, 50, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1120, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1220, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1220, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1220, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1270, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     2, 1220, 50, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1370, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1370, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1420, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1370, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1420, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1370, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1420, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1370, 100, 5 });
    }

    void GameUpdate(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies,GameContext& ctx, std::vector<std::shared_ptr<Lawnmower>>& lawnmowers)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(root, zombies);
        if (!finalWaveSpawned && AllZombiesDead(zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 2 });
            spawner.Spawn({ZombieSpawner::Type::Regular,3,570,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,0,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,50,4});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,640,0,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,50,5});
            spawner.Spawn({ZombieSpawner::Type::Conehead,2,620,50,5});
            finalWaveSpawned = true;
        }
        for (auto& lawnmower : lawnmowers) {
            lawnmower->Update(ctx);
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
    std::shared_ptr<Lawnmower> lawnmower;

};

#endif //LEVEL5_HPP
