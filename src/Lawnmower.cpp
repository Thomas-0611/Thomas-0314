//
// Created by Thomas on 2025/5/7.
//
#include "Lawnmower.hpp"

#include "plant/Plant.hpp"

Lawnmower::Lawnmower():AnimatedCharacter(std::vector<std::string>()) {
    std::vector<std::string> lawnmowerImages;
    lawnmowerImages.emplace_back(RESOURCE_DIR"/Day/Tool/Lawnmower.png");
    SetAnimation(lawnmowerImages);
    SetZIndex(2);
    SetPosition({-500, 0});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(200);
}
void Lawnmower::Update(GameContext &ctx) {
    if (!GetDead()) {
        if (!cleaning) {
            for (auto& zombie : ctx.zombies) {
                if (zombie->GetPosition().x - 25 <= GetPosition().x) {
                    cleaning = true;
                    break;
                }
            }
        }
        else {
            if (GetPosition().x >= 285) {
                SetDead();
            }
            else {
                SetPosition({GetPosition().x+5,GetPosition().y});
                //中間的範圍在25~72
                //清除植物
                for (auto& plant : ctx.plants) {
                    if (plant->GetPosition().y<25 && plant->GetPosition().y>-72) {
                        // 取得植物位置
                        printf("fuck\n");
                        glm::vec2 plantPos = plant->GetPosition();
                        if (plantPos.x <= GetPosition().x) {
                            printf("find\n");
                            // 找出該植物對應的 grid button（用最靠近的匹配）
                            for (auto& button : ctx.grid_buttons) {
                                glm::vec2 btnPos = button->GetButtonPosition();
                                float cellWidth = ctx.grid_buttons[1]->GetButtonPosition().x - ctx.grid_buttons[0]->GetButtonPosition().x;
                                float cellHeight = ctx.grid_buttons[9]->GetButtonPosition().y - ctx.grid_buttons[0]->GetButtonPosition().y;

                                // 判斷 plant 是否在此格內（你也可以依你 Button 實作調整這個邏輯）
                                if (std::abs(plantPos.x - btnPos.x) < cellWidth / 2 &&
                                    std::abs(plantPos.y - btnPos.y) < cellHeight / 2) {
                                    button->Setm_has_plant(false);
                                    break;
                                    }
                            }
                            ctx.to_remove_plants.push_back(plant.get());
                        }
                    }
                }
                //清除殭屍
                for (auto& zombie : ctx.zombies) {
                    if (zombie->GetPosition().y<25 && zombie->GetPosition().y>-72 && zombie->GetPosition().x<=GetPosition().x) {
                        zombie->Setlife(0);
                        zombie->SetDead();
                    }
                }
            }
        }
    }
}
void Lawnmower::Cleanall(GameContext &ctx) {

}

