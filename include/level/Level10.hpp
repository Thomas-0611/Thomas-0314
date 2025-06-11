//
// Created by Thomas on 2025/5/19.
//

#ifndef LEVEL10_HPP
#define LEVEL10_HPP
#include "Level.hpp"

class Level10:public Level {
public:
    Level10() = default;
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

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 520, 200, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 520, 200, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 520, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 600, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 600, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Buckethead,     1, 800, 100, 4 });

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1060, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 900, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 900, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 900, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1160, 100, 1 });

        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1240, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     2, 1160, 80, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1320, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1320, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1320, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1380, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1320, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Buckethead,     1, 1320, 100, 5 });

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1480, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1480, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Polevaulter,     1, 1520, 100, 4 });

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1720, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Buckethead,     1, 1720, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Polevaulter,     1, 1800, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 1720, 100, 5 });
    }

    void GameUpdate(GameContext& ctx)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!finalWaveSpawned && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 1 });
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,30,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,600,50,4});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,570,50,5});

            spawner.Spawn({ZombieSpawner::Type::Conehead,1,740,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,740,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,740,50,3});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,740,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,770,30,5});

            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,810,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,840,30,1});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,810,50,2});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,810,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,810,50,4});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,810,50,5});

            spawner.Spawn({ZombieSpawner::Type::Conehead,2,1050,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,1050,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,1050,30,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,1050,50,4});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,1050,30,5});

            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,1200,50,1});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,1310,30,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,1310,30,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,1200,30,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,1260,50,4});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,1230,50,5});

            spawner.Spawn({ZombieSpawner::Type::Polevaulter,2,1410,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,1300,50,2});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,1300,30,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,1330,50,3});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,1300,50,4});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,1300,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,1330,50,5});

            spawner.Spawn({ZombieSpawner::Type::Buckethead,2,1400,50,1});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,1400,50,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,1550,30,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,1400,50,4});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,1400,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,1430,50,5});
            finalWaveSpawned = true;
        }
        if (finalWaveSpawned && !finalWaveSpawned_2 && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ZombieSpawner::Type::Flag,1,520,50,3});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,3,550,30,1});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,550,50,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,4,600,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,5,570,30,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,3,570,30,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,660,30,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,3,570,30,4});
            spawner.Spawn({ZombieSpawner::Type::Buckethead,1,660,30,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,690,30,4});
            spawner.Spawn({ZombieSpawner::Type::Conehead,3,570,30,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,3,660,30,5});
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
#endif //LEVEL10_HPP
