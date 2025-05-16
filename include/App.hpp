#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "AnimatedCharacter.hpp"
#include "zombie/Zombie.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "Util/Renderer.hpp"
#include "Button.hpp"
#include "Lawnmower.hpp"
#include "plant/Sun.hpp"
#include "plant/Plant.hpp"
#include "plant/Snowpea.hpp"
#include "LevelManager.hpp"


class App {
public:
    enum class State {
        START,
        CHOOSE,
        UPDATE,
        END,
    };

    //每新增植物種類需添加新的植物進去
    enum class ChoosePlant {
        NONE,
        PEASHOOTER,
        REPEATER,
        SUNFLOWER,
        WALLNUT,
        SNOWPEASHOOTER,
        CHOMPER,
        CHERRYBOMB,
        POTATOMINE,
    };

    State GetCurrentState() const { return m_CurrentState; }
    void Setstartonce() {
        startonce = false;
    }

    void Setworldfreq(int value) {
        world_freq = value;
    }
    int Getworldfreq() {
        return world_freq;
    }
    void Setsunnum(int value) {
        sun_num += value;
    }
    int Getsunnum() {
        return sun_num;
    }

    //放置植物
    template <typename PlantType>
    void PlacePlant(int cost){
        if(choose != ChoosePlant::NONE) {
            for (int i = 0; i < 9; i++) {
                for (int j = 2-(button_number-1)/2; j < (button_number+1)/2+2; j++) {
                    int index = 9 * j + i;
                    if (grid_buttons[index]->MouseClickDetect() && !grid_buttons[index]->Getm_has_plant() && Getsunnum() >= cost){
                        auto plant = std::make_shared<PlantType>();
                        auto place_pos = grid_buttons[index]->GetButtonPosition();
                        plant->SetPosition(place_pos);
                        plant->SetGridButton(grid_buttons[index]);
                        plants.push_back(plant);
                        m_Root.AddChild(plant);
                        Setsunnum(-cost);
                        choose = ChoosePlant::NONE;
                        grid_buttons[index]->Setm_has_plant(true);
                    }
                }
            }
        }
    }
    void clearall() {
        // 移除所有植物
        for (auto& plant : plants) {
            // 取得植物位置
            glm::vec2 plantPos = plant->GetPosition();

            // 找出該植物對應的 grid button（用最靠近的匹配）
            for (auto& button : grid_buttons) {
                glm::vec2 btnPos = button->GetButtonPosition();
                float cellWidth = grid_buttons[1]->GetButtonPosition().x - grid_buttons[0]->GetButtonPosition().x;
                float cellHeight = grid_buttons[9]->GetButtonPosition().y - grid_buttons[0]->GetButtonPosition().y;

                // 判斷 plant 是否在此格內（你也可以依你 Button 實作調整這個邏輯）
                if (std::abs(plantPos.x - btnPos.x) < cellWidth / 2 &&
                    std::abs(plantPos.y - btnPos.y) < cellHeight / 2) {
                    button->Setm_has_plant(false);
                    break;
                    }
            }

            m_Root.RemoveChild(plant);
        }
        plants.clear();

        // 移除所有豌豆
        for (auto& pea : peas) {
            m_Root.RemoveChild(pea);
        }
        peas.clear();

        // 移除所有雪豆
        for (auto& snowpea : snowpeas) {
            m_Root.RemoveChild(snowpea);
        }
        snowpeas.clear();

        // 移除所有太陽
        for (auto& sun : suns) {
            m_Root.RemoveChild(sun);
        }
        suns.clear();

        // 移除商店植物
        for (auto& sp : storeplants) {
            m_Root.RemoveChild(sp);
        }
        storeplants.clear();

        // 移除背景圖片
        if (m_store) {
            m_Root.RemoveChild(m_store);
            m_store = nullptr;
        }

        if (m_store_sun) {
            m_Root.RemoveChild(m_store_sun);
            m_store_sun = nullptr;
        }

        if (m_stage1) {
            m_Root.RemoveChild(m_stage1);
            m_stage1 = nullptr;
        }
        //移除割草機
        //m_Root.RemoveChild(lawnmower);
        for (auto& lm : lawnmowers) {
            m_Root.RemoveChild(lm);
        }
    };

    void Start();

    void Choose();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

    State m_CurrentState = State::START;

    Util::Renderer m_Root;
    bool startonce = true;
    //std::shared_ptr<Lawnmower> lawnmower;
    std::vector<std::shared_ptr<Lawnmower>> lawnmowers;
    std::vector<std::shared_ptr<Zombie>> zombies;  // 多個殭屍
    std::vector<std::shared_ptr<Button>> grid_buttons;
    int button_number;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<BackgroundImage> m_stagebackground;
    std::shared_ptr<BackgroundImage> m_stage1_3;
    std::shared_ptr<BackgroundImage> m_store;
    std::shared_ptr<BackgroundImage> m_store_sun;
    std::shared_ptr<BackgroundImage> m_stage1;
    std::vector<std::shared_ptr<Sun>> suns;
    std::vector<std::shared_ptr<BackgroundImage>> storeplants;
    int world_freq = 0;
    //嘗試多個豌豆射手
    std::vector<std::shared_ptr<Peashooter>> peashooters;  // 所有生成的 Peashooter
    std::vector<std::shared_ptr<Pea>> peas;
    std::vector<std::shared_ptr<Snowpea>> snowpeas;
    std::vector<std::shared_ptr<Plant>> plants;
    Button m_peashooters_button = Button(-565,-509,221,293);
    Button m_sunflower_button = Button(-508,-452,221,293);
    Button m_wallnut_button = Button(-451,-395,221,293);
    Button m_repeater_button = Button(-394,-338,221,293);
    Button m_snowpeashooter_button = Button(-337,-281,221,293);
    Button m_chomper_button = Button(-280,-224,221,293);
    Button m_cherrybomb_button = Button(-223,-167,221,293);
    Button m_potatomine_button = Button(-166,-110,221,293);
    Button m_start_button = Button(28,340,79,155);
    Button m_placeable_button = Button(-435,285,-270,225);

    Button m_left_stage = Button(-565,-329,109,340);
    Button m_middle_stage = Button(-108,123,109,340);
    Button m_right_stage = Button(345,576,109,340);

    int sun_num = 750;
    bool choosing_r = false;
    bool choosing_l = false;
    int move_bound = 0;
    glm::vec2 temp_pivot=glm::vec2(0,0);
    ChoosePlant choose = ChoosePlant::NONE;

    LevelManager level;

};

#endif
