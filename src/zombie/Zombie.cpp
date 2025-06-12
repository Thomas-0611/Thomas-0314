//
// Created by Thomas on 2025/3/20.
//
#include "zombie/Zombie.hpp"
#include "plant/Peashooter.hpp"
#include "plant/Plant.hpp"
#include "GameContext.hpp"
Zombie::Zombie()
    : AnimatedCharacter(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> zombieImages;
    for (int i = 0; i < 18; ++i) {
        zombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(walk)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }
    SetAnimation(zombieImages);
    SetZIndex(2);
    SetPosition({620, 15});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(200);
}

void Zombie::Update(GameContext& ctx) {
    // 當 20 秒內被射 5 顆以上，要被凍住 6 秒
    if (Get_snowpea_shooted() >= 5) {
        SetLooping(false);
        SetPlaying(false);
        Addfrozenfreq(1);
    }
    else {
        if (!m_dead) {
            SetLooping(true);
            SetPlaying(true);
            auto cur_pos = GetPosition();
            if (!m_targetPlant) {
                SetPosition({cur_pos[0] - 0.2, cur_pos[1]});
            }

            // test GPT Version
            // 我自己加的，如果target植物死了，直接erase掉
            if (m_targetPlant && m_targetPlant->Getlife()<=0) {
                auto it = std::find(ctx.plants.begin(), ctx.plants.end(), m_targetPlant);
                if (it != ctx.plants.end()) {
                    GetTargetPlant()->GetGridButton()->Setm_has_plant(false);
                    ctx.to_remove_plants.push_back(m_targetPlant.get());
                }
                m_targetPlant = nullptr;
                Setbacktomove();
            }
            // 如果沒有目標植物，就去找
            if (!m_targetPlant) {
                // 找新的碰撞目標
                for (auto& plant : ctx.plants) {
                    if (CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(plant))) {
                        m_targetPlant = plant;
                        SetEat();
                        break;
                    }
                }
            }

            // 如果有目標植物，處理吃的邏輯
            if (m_targetPlant) {
                if (CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(m_targetPlant))) {
                    if (cur_freq >= GetAttackfreq()) {
                        m_targetPlant->Setlife(m_targetPlant->Getlife() - GetAttackvalue());
                        cur_freq = 0;
                    } else {
                        Setcurfreq(cur_freq + 1);
                    }
                }
            }
        }
    }
    if (Get_snowpea_freq() >= 1200 || Getfrozenfreq() >= 360) {
        Add_snowpea_freq(-Get_snowpea_freq());
        Set_snowpea_shooted(0);
        // frozen_freq = 0;
        Addfrozenfreq(-Getfrozenfreq());
        Setstartcount(false);
    }
    // 被射到第一次才可以開始計算snowpea_freq
    if (Getstartcount() && Getfrozenfreq() == 0) {
        Add_snowpea_freq(1);
    }

}

void Zombie::SetEat() {
    if (!m_dead) {
        std::vector<std::string> zombieeatImages;
        for (int i = 0; i < 21; ++i) {
            zombieeatImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(eat)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(zombieeatImages);
        Seteatvalue(true);
    }
}

void Zombie::Setbacktomove() {
    std::vector<std::string> zombieImages;
    for (int i = 0; i < 18; ++i) {
        zombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(walk)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }
    SetAnimation(zombieImages);
    Seteatvalue(false);
    cur_freq = 0;
    m_targetPlant = nullptr;
}

void Zombie::SetDead() {
    if (!m_dead) {
        m_dead = true;
        if (!Getbeeaten()) {
            std::vector<std::string> zombiedeadImages;
            for (int i = 0; i < 10; ++i) {
                zombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
            }
            SetAnimation(zombiedeadImages);
        }
        SetLooping(false);
        SetPlaying(true);
    }
}
