//
// Created by Thomas on 2025/4/19.
//
#include "plant/Potatomine.hpp"

Potatomine::Potatomine()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> potatomineImages;
    for (int i = 0; i < 8; ++i) {
        potatomineImages.emplace_back(RESOURCE_DIR"/Day/Plant/PotatoMine(notready)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }
    SetAnimation(potatomineImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(300);
    SetAttackfreq(600);
    SetAttackvalue(1500);
}

void Potatomine::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);

        int freq = GetAttackfreq();
        if (cur_freq >= freq) {
            if (!ready) {
                Setreadymode();
            }
        }
        else {
            Setcurfreq(cur_freq+1);
        }

        if (ready) {
            //TODO:爆炸攻擊9宮格內的殭屍
            auto center = GetPosition();
            float w = ctx.grid_x;
            float h = ctx.grid_y;

            bool triggered = false;

            // 第一步：判斷有沒有殭屍「踩到」地雷本體
            for (auto& zombie : ctx.zombies) {
                if (zombie->GetDead()) continue;
                auto zpos = zombie->GetPosition();

                // 這裡是碰到地雷本體的範圍（可根據圖片微調）
                if (std::abs(zpos.x - center.x) <= w * 1.0f &&
                    std::abs(zpos.y - center.y) <= h * 1.0f) {
                    triggered = true;
                    break;
                    }
            }

            if (triggered) {
                Settoexplore(ctx);
            }
        }
    }
    else {
        SetDead();
        // 從 plants 中移除自己
        ctx.to_remove_plants.push_back(this);
    }
}
void Potatomine::Setreadymode() {
    std::vector<std::string> potatominereadyImages;
    for (int i = 0; i < 8; ++i) {
        potatominereadyImages.emplace_back(RESOURCE_DIR"/Day/Plant/PotatoMine(ready)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }
    SetAnimation(potatominereadyImages);
    ready = true;
}

void Potatomine::Settoexplore(GameContext& ctx) {
    std::vector<std::string> potatomineexploreImages;
    for (int i = 0; i < 4; ++i) {
        potatomineexploreImages.emplace_back(RESOURCE_DIR"/Day/Plant/PotatoMine(toexplore)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }
    SetAnimation(potatomineexploreImages);
    for (auto& zombie : ctx.zombies) {
        auto center = GetPosition();
        float w = ctx.grid_x;
        float h = ctx.grid_y;
        if (zombie->GetDead()) continue;
        auto zpos = zombie->GetPosition();

        if (std::abs(zpos.x - center.x) <= w * 1.5f &&
            std::abs(zpos.y - center.y) <= h * 1.5f) {
            zombie->Setlife(zombie->Getlife() - GetAttackvalue());
            if (zombie->Getlife() <= 0) {
                zombie->SetDead();
            }
        }
    }
    Setlife(0);
}

