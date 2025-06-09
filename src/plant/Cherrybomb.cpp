//
// Created by Thomas on 2025/4/18.
//
#include "plant/Cherrybomb.hpp"

Cherrybomb::Cherrybomb()
    : Plant(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> cherrybombImages;
    for (int i = 0; i < 7; ++i) {
        cherrybombImages.emplace_back(RESOURCE_DIR"/Day/Plant/CherryBomb/frame_" + std::to_string(i) + "_delay-0.09s.png");
    }
    SetAnimation(cherrybombImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(300);
    SetAttackfreq(60);
    SetAttackvalue(1500);
}

void Cherrybomb::Explode(GameContext& ctx) {
    auto center = GetPosition();
    float w = ctx.grid_x;
    float h = ctx.grid_y;

    for (auto& zombie : ctx.zombies) {
        if (zombie->GetDead() || !zombie->Getontheground()) continue;
        auto zpos = zombie->GetPosition();
        if (std::abs(zpos.x - center.x) <= w * 1.5f && std::abs(zpos.y - center.y) <= h * 1.5f) {
            zombie->Setlife(zombie->Getlife() - GetAttackvalue());
            if (zombie->Getlife() <= 0) zombie->SetDead();
        }
    }
}


void Cherrybomb::Update(GameContext& ctx) {
    if (Getlife() > 0) {
        SetLooping(true);
        SetPlaying(true);

        int freq = GetAttackfreq();
        if (cur_freq >= freq) {
            //TODO:爆炸攻擊9宮格內的殭屍
            Explode(ctx);
            Setlife(0); // 爆炸後自我銷毀
        }
        else {
            Setcurfreq(cur_freq+1);
        }
    }
    else {
        SetDead();
        // 從 plants 中移除自己
        GetGridButton()->Setm_has_plant(false);
        ctx.to_remove_plants.push_back(this);
    }
}
