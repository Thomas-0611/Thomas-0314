//
// Created by tommy on 2025/5/1.
//

#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include "Level.hpp"
#include "Shovel.hpp"

class Level1:public Level {
public:
    Level1() = default;
    void Load(GameContext& ctx) override {
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!m_stage) {
            m_stage = std::make_shared<BackgroundImage>();
            m_stage->SetBackgroundImage("one");
            m_stage->SetZIndex(-9);
            ctx.m_Root.AddChild(m_stage);
        } else {
            m_stage->SetBackgroundImage("one");
            m_stage->SetZIndex(-9);
        }

        ctx.button_number = 1;//輸入1or3or5
        
        for(int i = 3; i < 4; i++) {
            lawnmower = std::make_shared<Lawnmower>(i);
            ctx.lawnmowers.emplace_back(lawnmower);
            ctx.m_Root.AddChild(lawnmower);
        }

        int storeplantCount = 1; // 可以調整植物生成數量

        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            ctx.storeplants.push_back(storeplant);
            ctx.m_Root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     3, 520, 100, 3 });
    }

    void GameUpdate(GameContext& ctx)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!finalWaveSpawned && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 3 });
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,0,3});
            finalWaveSpawned = true;
        }
        for (auto& lawnmower : ctx.lawnmowers) {
            lawnmower->Update(ctx);
        }
        //更新鏟子


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

#endif //LEVEL1_HPP
