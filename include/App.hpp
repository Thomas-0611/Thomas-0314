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
#include "level/LevelManager.hpp"
#include "Shovel.hpp"


class App {
public:
    enum class State {
        START,
        CHOOSE,
        UPDATE,
        PAUSE,
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
    void Resetsunnum() {
        sun_num = 200;
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

        // 移除所有殭屍
        for (auto& zombie : zombies) {
            m_Root.RemoveChild(zombie);
        }
        zombies.clear();

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
        m_stage1_3->SetZIndex(0);
        m_stagebackground->SetZIndex(-1);
        if (m_store) {
            m_Root.RemoveChild(m_store);
            m_store = nullptr;
        }

        if (m_store_sun) {
            m_Root.RemoveChild(m_store_sun);
            m_store_sun = nullptr;
        }

        //移除割草機
        //m_Root.RemoveChild(lawnmower);
        for (auto& lm : lawnmowers) {
            m_Root.RemoveChild(lm);
        }
        lawnmowers.clear();

        //移除太陽數字
        for (auto& lm : m_store_suns) {
            m_Root.RemoveChild(lm);
        }
        m_store_suns.clear();
        Resetsunnum();

        //移除鏟子
        m_Root.RemoveChild(shovel);
    };

    void SwitchToLevel(int levelId, GameContext& ctx) {
        if (level.Getcurrentlevel()) {
            level.Getcurrentlevel()->RemoveStage(m_Root);
            level.Setlevlenull();
        }
        level.LoadLevel(levelId, ctx);
        // lawnmower = std::make_shared<Lawnmower>();
        // m_Root.AddChild(lawnmower);
        m_stagebackground->SetZIndex(-100);
        m_stage1_3->SetZIndex(-100);

        m_store = std::make_shared<BackgroundImage>();
        m_store->SetBackgroundImage("store_long");
        m_store->SetPivot({350,-256});
        m_store->SetZIndex(-8);
        m_Root.AddChild(m_store);

        for(int i = 0; i < 5; i++) {
            m_store_sun = std::make_shared<BackgroundImage>();
            // 太陽花的數量顯示
            m_store_sun->SetBackgroundImage("Sun_num/digit_0");
            m_store_sun->SetPivot({589+8*i,-227});
            m_store_sun->SetZIndex(-7);
            m_store_suns.push_back(m_store_sun);
            m_Root.AddChild(m_store_sun);
        }
        shovel = std::make_shared<Shovel>();
        m_Root.AddChild(shovel);

        m_CurrentState = State::UPDATE;
    }


    void Start();

    void Choose();

    void Update();
    void Pause();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

    State m_CurrentState = State::START;

    Util::Renderer m_Root;
    bool startonce = true;
    std::shared_ptr<Shovel> shovel;
    std::vector<std::shared_ptr<Lawnmower>> lawnmowers;
    std::vector<std::shared_ptr<Zombie>> zombies;  // 多個殭屍
    std::vector<std::shared_ptr<Button>> grid_buttons;
    int button_number;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<BackgroundImage> m_Paused;
    std::shared_ptr<BackgroundImage> m_Pausedpage;
    std::shared_ptr<BackgroundImage> m_stagebackground;
    std::shared_ptr<BackgroundImage> m_stage1_3;
    std::shared_ptr<BackgroundImage> m_store;
    std::shared_ptr<BackgroundImage> m_store_sun;
    std::vector<std::shared_ptr<BackgroundImage>> m_store_suns;
    std::vector<std::shared_ptr<Sun>> suns;
    std::vector<std::shared_ptr<BackgroundImage>> storeplants;
    int world_freq = 0;
    //嘗試多個豌豆射手
    std::vector<std::shared_ptr<Peashooter>> peashooters;  // 所有生成的 Peashooter
    std::vector<std::shared_ptr<Pea>> peas;
    std::vector<std::shared_ptr<Snowpea>> snowpeas;
    std::vector<std::shared_ptr<Plant>> plants;
    std::vector<Button> m_plant_buttons = {
        Button(-565,-509,221,293), // PEASHOOTER
        Button(-508,-452,221,293), // SUNFLOWER
        Button(-451,-395,221,293), // WALLNUT
        Button(-394,-338,221,293), // REPEATER
        Button(-337,-281,221,293), // SNOWPEASHOOTER
        Button(-280,-224,221,293), // CHOMPER
        Button(-223,-167,221,293), // CHERRYBOMB
        Button(-166,-110,221,293)  // POTATOMINE
    };

    std::vector<int> sun_cost = {100, 50, 50, 150, 150, 200, 200, 125};

    // 植物對應的選擇枚舉（需與 ChoosePlant Enum 對應順序一致）
    std::vector<ChoosePlant> plant_types = {
        ChoosePlant::PEASHOOTER,
        ChoosePlant::SUNFLOWER,
        ChoosePlant::WALLNUT,
        ChoosePlant::REPEATER,
        ChoosePlant::SNOWPEASHOOTER,
        ChoosePlant::CHOMPER,
        ChoosePlant::CHERRYBOMB,
        ChoosePlant::POTATOMINE
    };

    Button m_start_button = Button(28,340,79,155);
    Button m_placeable_button = Button(-435,285,-270,225);

    Button m_left_stage = Button(-565,-329,109,340);
    Button m_middle_stage = Button(-108,123,109,340);
    Button m_right_stage = Button(345,576,109,340);

    Button m_shovel = Button(-50,50,221,293);

    Button m_menu_button = Button(-120,100,-221,-177);
    Button m_continue_button = Button(-232,-10,-171,-129);
    Button m_restart_button = Button(-9,216,-171,-129);
    Button m_paused_button = Button(520,635,190,300);
    int sun_num = 200;
    bool choosing_r = false;
    bool choosing_l = false;
    int move_bound = 0;
    glm::vec2 temp_pivot=glm::vec2(0,0);
    ChoosePlant choose = ChoosePlant::NONE;
    bool cheatmode = false;

    LevelManager level;

    int max_level_cleared = 0; // 預設只開放第一關
    int current_level = 0;     // 紀錄目前進行的關卡

    bool paused = false;
    int stage_to_enter = 1;
    bool pausedpageadded = false;

};

#endif
