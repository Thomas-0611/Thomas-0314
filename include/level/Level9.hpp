//
// Created by Thomas on 2025/5/18.
//

#ifndef LEVEL9_HPP
#define LEVEL9_HPP
#include "Level.hpp"

class Level9:public Level {
public:
    Level9() = default;
    void Load(GameContext& ctx) override {
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);

        if (!m_stage) {
            m_stage = std::make_shared<BackgroundImage>();
            m_stage->SetBackgroundImage("five");
            m_stage->SetZIndex(-9);

            ctx.m_Root.AddChild(m_stage);
        } else {
            m_stage->SetBackgroundImage("five");
            m_stage->SetZIndex(-9);
        }

        ctx.button_number = 5;//輸入1or3or5

        for(int i = 1; i < 6; i++) {
            lawnmower = std::make_shared<Lawnmower>(i);
            ctx.lawnmowers.emplace_back(lawnmower);
            ctx.m_Root.AddChild(lawnmower);
        }

        int storeplantCount = 8; // 可以調整植物生成數量 要再改成櫻桃炸彈
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            ctx.storeplants.push_back(storeplant);
            ctx.m_Root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 520, 200, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 620, 200, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 700, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 800, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 800, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 900, 250, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 900, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1000, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1120, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Polevaulter,     1, 1220, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1220, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1220, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1300, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1300, 100, 1 });
    }

    void GameUpdate(GameContext& ctx)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!finalWaveSpawned && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 5 });
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,30,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,50,4});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,600,0,4});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,670,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,630,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,630,50,3});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,690,50,4});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,690,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,720,30,3});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,720,30,5});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,750,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,750,50,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,750,30,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,780,30,1});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,780,50,5});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,810,50,1});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,810,50,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,810,50,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,840,30,4});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,840,50,5});

            spawner.Spawn({ZombieSpawner::Type::Regular,1,870,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,870,50,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,920,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,870,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,870,50,5});

            spawner.Spawn({ZombieSpawner::Type::Conehead,1,900,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,900,50,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,970,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,900,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,900,50,5});

            finalWaveSpawned = true;
        }
        if (finalWaveSpawned && !finalWaveSpawned_2 && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ZombieSpawner::Type::Flag,1,520,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,3,550,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,550,50,2});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,570,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,550,30,3});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,550,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,30,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,550,30,5});
            finalWaveSpawned_2 = true;
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
    bool finalWaveSpawned_2 = false;

    std::shared_ptr<Lawnmower> lawnmower;

};
#endif //LEVEL9_HPP
