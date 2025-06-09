//
// Created by Thomas on 2025/5/15.
//

#ifndef LEVEL7_HPP
#define LEVEL7_HPP
#include "Level.hpp"

class Level7:public Level {
public:
    Level7() = default;
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

        int storeplantCount = 7; // 可以調整植物生成數量 要再改成櫻桃炸彈
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
            storeplant->SetZIndex(-7);
            storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
            ctx.storeplants.push_back(storeplant);
            ctx.m_Root.AddChild(storeplant);
        }

        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 520, 200, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 620, 200, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 720, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 800, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 880, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Conehead,     1, 960, 250, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1000, 100, 1 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1000, 100, 2 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1000, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Polevaulter,     1, 1120, 100, 3 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1120, 100, 4 });
        spawner.Spawn({ ZombieSpawner::Type::Polevaulter,     1, 1200, 100, 5 });
        spawner.Spawn({ ZombieSpawner::Type::Regular,     1, 1280, 100, 1 });
    }

    void GameUpdate(GameContext& ctx)override {
        // 檢查 zombies 中是否沒有第一階段的殭屍
        ZombieSpawner spawner(ctx.m_Root, ctx.zombies);
        if (!finalWaveSpawned && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ ZombieSpawner::Type::Flag,1, 520, 0, 4 });
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,30,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,600,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,0,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,630,50,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,630,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,630,50,5});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,670,50,1});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,670,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,700,30,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,700,30,2});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,700,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,700,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,750,30,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,750,30,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,750,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,750,50,5});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,780,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,780,50,2});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,780,30,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,820,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,820,50,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,820,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,820,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,850,50,1});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,850,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,850,50,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,850,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,850,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,890,50,1});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,890,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,890,50,4});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,890,50,5});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,920,50,1});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,920,50,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,920,30,3});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,920,50,4});
            finalWaveSpawned = true;
        }
        if (finalWaveSpawned && !finalWaveSpawned_2 && AllZombiesDead(ctx.zombies)) {
            spawner.Spawn({ZombieSpawner::Type::Flag,1,520,50,1});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,520,50,3});
            spawner.Spawn({ZombieSpawner::Type::Polevaulter,1,520,50,5});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,1,570,50,3});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,570,50,4});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,570,30,5});
            spawner.Spawn({ZombieSpawner::Type::Conehead,1,620,50,1});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,620,30,2});
            spawner.Spawn({ZombieSpawner::Type::Regular,2,620,30,4});
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
#endif //LEVEL7_HPP
