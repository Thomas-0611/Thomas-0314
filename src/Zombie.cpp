//
// Created by Thomas on 2025/3/20.
//
#include "zombie/Zombie.hpp"
#include "plant/Peashooter.hpp"
#include "plant/Plant.hpp"
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

void Zombie::Update(std::vector<std::shared_ptr<Plant>>& plants) {
    if (!m_dead) {
        SetLooping(true);
        SetPlaying(true);
        auto cur_pos = GetPosition();
        if (!GetEating()) {
            SetPosition({cur_pos[0] - 0.15, cur_pos[1]});
        }

        // my version

        // if (Getlife() <= 0 ) {
        //     SetDead();
        // }
        // else {
        //     // 現在有一個bug，當有2個植物在時，且有殭屍正在吃其中一隻植物，殭屍會因為通過第三個判斷條件，導致動畫卡住
        //     for (auto& plant: plants) {
        //         if (CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(plant)) && !GetEating()) {
        //             SetEat();
        //         }
        //         else if (CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(plant)) && GetEating()) {
        //             if (cur_freq >= GetAttackfreq()) {
        //                 plant->Setlife(plant->Getlife() - GetAttackvalue());
        //                 cur_freq = 0;
        //             }
        //             else {
        //                 Setcurfreq(cur_freq+1);
        //             }
        //         }
        //         else if (!CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(plant)) && GetEating()) {
        //             Setbacktomove();
        //         }
        //         printf("left:: %d\n",plant->Getlife());
        //     }

        // test GPT Version
        // 還是會有bug，當有兩個植物以上，當下的目標死掉後，還是會卡住，但是變成在原地一直吃
        if (!m_targetPlant || m_targetPlant->Getlife() <= 0) {
            // 找新的碰撞目標
            for (auto& plant : plants) {
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
            } else {
                // 與目標植物已分開
                Setbacktomove();
            }
        }
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
        std::vector<std::string> zombiedeadImages;
        for (int i = 0; i < 10; ++i) {
            zombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(zombiedeadImages);
        SetLooping(false);
        SetPlaying(true);
    }
}
