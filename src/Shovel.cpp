//
// Created by Thomas on 2025/5/23.
//
#include "Shovel.hpp"

#include "plant/Plant.hpp"
Shovel::Shovel():AnimatedCharacter(std::vector<std::string>()) {
    std::vector<std::string> shovelImages;
    shovelImages.emplace_back(RESOURCE_DIR"/Day/Tool/Shovel.png");
    SetAnimation(shovelImages);
    SetZIndex(7);
    SetPosition({0, 257});
    SetVisible(true);
    SetPlaying(true);
    SetLooping(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(200);
}
void Shovel::Clean(GameContext &ctx, glm::vec2 pos) {
    if (Clicked) {
        float cellheight = ctx.grid_buttons[9]->GetButtonPosition().y - ctx.grid_buttons[0]->GetButtonPosition().y;
        float cellwidth = ctx.grid_buttons[1]->GetButtonPosition().x - ctx.grid_buttons[0]->GetButtonPosition().x;
        for (auto& plant : ctx.plants) {
            auto plantPos = plant->GetPosition();
            if (pos.x <= plantPos.x+(cellwidth/2) &&
                pos.x >= plantPos.x-(cellwidth/2) &&
                pos.y <= plantPos.y+(cellheight/2) &&
                pos.y >= plantPos.y-(cellheight/2) ) {
                // 找出該植物對應的 grid button（用最靠近的匹配）
                for (auto& button : ctx.grid_buttons) {
                    glm::vec2 btnPos = button->GetButtonPosition();
                    // 判斷 plant 是否在此格內（你也可以依你 Button 實作調整這個邏輯）
                    if (std::abs(plantPos.x - btnPos.x) < cellwidth / 2 &&
                        std::abs(plantPos.y - btnPos.y) < cellheight / 2) {
                        button->Setm_has_plant(false);
                        break;
                        }
                }
                ctx.to_remove_plants.push_back(plant.get());
                plant->Setlife(0);
                plant->SetDead();
                break;
                }
        }
    }
}
