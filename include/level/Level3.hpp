//
// Created by Thomas on 2025/5/12.
//

#ifndef LEVEL3_HPP
#define LEVEL3_HPP

#include "Level.hpp"

class Level3:public Level {
public:
    Level3() = default;
    void Load(GameContext& ctx) override {
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);

        if (!m_stage) {
            m_stage = std::make_shared<BackgroundImage>();
            m_stage->SetBackgroundImage("three");
            m_stage->SetZIndex(-9);

            ctx.m_Root.AddChild(m_stage);
        } else {
            m_stage->SetBackgroundImage("three");
            m_stage->SetZIndex(-9);
        }

        ctx.button_number = 3;//輸入1or3or5

        for(int i = 2; i < 5; i++) {
            lawnmower = std::make_shared<Lawnmower>(i);
            ctx.lawnmowers.emplace_back(lawnmower);
            ctx.m_Root.AddChild(lawnmower);
        }

        int storeplantCount = 3; // 可以調整植物生成數量 要再改成櫻桃炸彈
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            ctx.storeplants.push_back(storeplant);
            ctx.m_Root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     2, 520, 200, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 820, 200, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 970, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 600, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 600, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     2, 700, 250, 4 });
    }

    void GameUpdate(GameContext& ctx)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!finalWaveSpawned && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 2 });
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,0,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,620,50,4});
            finalWaveSpawned = true;
        }
        for (auto& lawnmower : ctx.lawnmowers) {
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

#endif //LEVEL3_HPP
