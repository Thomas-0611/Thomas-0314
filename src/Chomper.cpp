//
// Created by Thomas on 2025/4/20.
//
#include "plant/Chomper.hpp"

Chomper::Chomper()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> ChomperImages;
    for (int i = 0; i < 13; ++i) {
        ChomperImages.emplace_back(RESOURCE_DIR"/Day/Plant/Chomper/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(ChomperImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(300);
}

void Chomper::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);

        auto center = GetPosition();
        float w = ctx.grid_x;
        float h = ctx.grid_y;

        if (!starteat) {
            for (auto& zombie : ctx.zombies) {
                if (zombie->GetDead()) continue;
                auto zpos = zombie->GetPosition();

                if (std::abs(zpos.x - center.x) <= w * 0.5f &&
                    std::abs(zpos.y - center.y) <= h * 0.5f) {
                    m_targetzombie = zombie;
                    // 殭屍進入被咬的範圍
                    starteat = true;
                    eating_timer = 1800; // 約 30 秒
                    std::vector<std::string> ChompereatImages;
                    for (int i = 0; i < 9; ++i) {
                        ChompereatImages.emplace_back(RESOURCE_DIR"/Day/Plant/Chomper(eat)/frame_" + std::to_string(i) + "_delay-0.18s.png");
                    }
                    SetAnimation(ChompereatImages);
                    break;
                }
            }
        } else {
            // 檢查eat的動畫播完沒，播完了後切到ate
            if (IfAnimationEnds() && !eating) {
                if (m_targetzombie->Getontheground()) {
                    Seteating(ctx);
                }
                else {
                    Setbacktonormal();
                    starteat = false;
                    m_targetzombie = nullptr;
                }
            }
            if (eating) {
                if (eating_timer > 0) {
                    eating_timer--;
                }
                else {
                    Setbacktonormal();
                }
            }
        }
    }
    else {
        SetDead();
    }
}


void Chomper::Seteating(GameContext& ctx) {
    for (auto& zombie : ctx.zombies) {
        auto center = GetPosition();
        float w = ctx.grid_x;
        float h = ctx.grid_y;
        if (zombie->GetDead()) continue;

        auto zpos = zombie->GetPosition();

        if (std::abs(zpos.x - center.x) <= w * 0.7f &&
            std::abs(zpos.y - center.y) <= h * 0.7f) {

            std::vector<std::string> ChompereatingImages;
            for (int i = 0; i < 6; ++i) {
                ChompereatingImages.emplace_back(RESOURCE_DIR"/Day/Plant/Chomper(ate)/frame_" + std::to_string(i) + "_delay-0.18s.png");
            }
            SetAnimation(ChompereatingImages);
            zombie->Setbeeaten(true);
            zombie->Setlife(0);
            zombie->SetDead();
            eating = true;
            break;
        }
    }
    // 假設食人花原先有目標，但因為被其他植物殺死了，導致目標物消失，而導致空吃，為避免以上狀況而設計的
    if (!eating) {
        Setbacktonormal();
    }
}

void Chomper::Setbacktonormal() {
    std::vector<std::string> ChomperImages;
    for (int i = 0; i < 13; ++i) {
        ChomperImages.emplace_back(RESOURCE_DIR"/Day/Plant/Chomper/frame_" + std::to_string(i) + "_delay-0.18s.png");
    }
    SetAnimation(ChomperImages);
    starteat = false;
    eating = false;
}