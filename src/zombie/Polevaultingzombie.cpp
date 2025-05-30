//
// Created by Thomas on 2025/4/8.
//
#include "zombie/Polevaultingzombie.hpp"

#include "GameContext.hpp"
#include "plant/Plant.hpp"

Polevaultingzombie::Polevaultingzombie() : Zombie(){
    std::vector<std::string> PolevaultingzombieImages;
    for (int i = 1; i < 52; ++i) {
        PolevaultingzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/PoleVaultingZombie(walk)_resized/frame_" + std::to_string(i) + ".png");
    }
    SetAnimation(PolevaultingzombieImages);
    SetZIndex(2);
    SetPosition({620, 15});
    SetVisible(true);
    Setlife(1600);
    SetAttackfreq(180);
    SetAttackvalue(200);
}


void Polevaultingzombie::Update(GameContext& ctx) {
    if (Get_snowpea_shooted() >= 5) {
        SetLooping(false);
        SetPlaying(false);
        Addfrozenfreq(1);
    }
    else {
        if (!GetDead()) {
            SetLooping(true);
            SetPlaying(true);
            auto cur_pos = GetPosition();
            if (!GetTargetPlant()) {
                if (!firsttouch) {
                    SetPosition({cur_pos[0] - 0.4, cur_pos[1]});
                }
                else {
                    SetPosition({cur_pos[0] - 0.3, cur_pos[1]});
                }
            }
            // 當正在跳躍的時候，要去檢查是不是跳躍畫面的最後一幀了
            if (jumping) {
                // TODO 檢查是不是最後一幀
                if (IfAnimationEnds()) {
                    jumping = false;
                    firsttouch = true;
                    Setbacktomove();
                    SetPosition({cur_pos[0] - 150, cur_pos[1]});
                }
            }

            // test GPT Version
            // 我自己加的，如果target植物死了，直接erase掉
            if (GetTargetPlant() && GetTargetPlant()->Getlife()<=0) {
                auto it = std::find(ctx.plants.begin(), ctx.plants.end(), GetTargetPlant());
                if (it != ctx.plants.end()) {
                    GetTargetPlant()->GetGridButton()->Setm_has_plant(false);
                    ctx.to_remove_plants.push_back(GetTargetPlant().get());
                }
                Set_m_targetnull();
                if(!jumping) {
                    Setbacktomove();
                }
            }
            // 如果沒有目標植物，就去找
            if (!GetTargetPlant()) {
                // 找新的碰撞目標
                for (auto& plant : ctx.plants) {
                    if (CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(plant))) {
                        // TODO 第一次遇到植物要跳躍超過它
                        if (!firsttouch) {
                            SetJump();
                            Set_targetplant(plant);
                            jumping = true;
                        }
                        else {
                            Set_targetplant(plant);
                            SetEat();
                        }
                        break;
                    }
                }
            }

            // 如果有目標植物，處理吃的邏輯
            if (GetTargetPlant()) {
                if (CheckCollisionZombie(std::static_pointer_cast<AnimatedCharacter>(GetTargetPlant()))) {
                    if (Getcurfreq() >= GetAttackfreq()) {
                        GetTargetPlant()->Setlife(GetTargetPlant()->Getlife() - GetAttackvalue());
                        // cur_freq = 0;
                        Setcurfreq(0);
                    } else {
                        Setcurfreq(Getcurfreq() + 1);
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

void Polevaultingzombie::SetJump() {
    if (!GetDead()) {
        Setontheground(false);
        std::vector<std::string> PolevaultingzombiejumpImages;
        for (int i = 52; i < 94; ++i) {
            PolevaultingzombiejumpImages.emplace_back(RESOURCE_DIR"/Day/Zombie/PoleVaultingZombie(action)_resized/frame_" + std::to_string(i) + ".png");
        }
        SetAnimation(PolevaultingzombiejumpImages);
    }
}


void Polevaultingzombie::SetEat(){
    if (!GetDead()) {
        std::vector<std::string> PolevaultingzombieeatImages;
        for (int i = 166; i < 194; ++i) {
            PolevaultingzombieeatImages.emplace_back(RESOURCE_DIR"/Day/Zombie/PoleVaultingZombie(eat)_resized/frame_" + std::to_string(i) + ".png");
        }
        SetAnimation(PolevaultingzombieeatImages);
        Seteatvalue(true);
    }
}

void Polevaultingzombie::Setbacktomove(){
    Setontheground(true);
    std::vector<std::string> PolevaultingzombieImages;
    for (int i = 94; i < 114; ++i) {
        PolevaultingzombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/PoleVaultingZombie(walk_non)_resized/frame_" + std::to_string(i) + ".png");
    }
    SetAnimation(PolevaultingzombieImages);
    Seteatvalue(false);
    Setcurfreq(0);
    Set_m_targetnull();
}

void Polevaultingzombie::SetDead(){
    if (!GetDead()) {
        Set_m_dead(true);
        if (!Getbeeaten()) {
            std::vector<std::string> PolevaultingzombiedeadImages;
            for (int i = 130; i < 166; ++i) {
                PolevaultingzombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/PoleVaultingZombie(dead)_resized/frame_" + std::to_string(i) + ".png");
            }
            SetAnimation(PolevaultingzombiedeadImages);
        }
        SetLooping(false);
        SetPlaying(true);
    }
}