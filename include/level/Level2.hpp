//
// Created by Thomas on 2025/5/9.
//

#ifndef LEVEL2_HPP
#define LEVEL2_HPP

#include "Level.hpp"

class Level2:public Level {
public:
    Level2() = default;
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

        int storeplantCount = 2; // 可以調整植物生成數量
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            ctx.storeplants.push_back(storeplant);
            ctx.m_Root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     3, 520, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     2, 520, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     2, 520, 100, 3 });
    }

    void GameUpdate(GameContext& ctx)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!finalWaveSpawned && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 2 });
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,0,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,0,4});
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

#endif //LEVEL2_HPP
