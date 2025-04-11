#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "AnimatedCharacter.hpp"
#include "zombie/Zombie.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "Util/Renderer.hpp"
#include "Button.hpp"
#include "plant/Sun.hpp"
#include "plant/Plant.hpp"


class App {
public:
    enum class State {
        START,
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
                for (int j = 0; j < 5; j++) {
                    int index = 9 * j + i;
                    if (grid_buttons[index]->MouseClickDetect() && !grid_buttons[index]->m_has_plant && Getsunnum() >= cost){
                        auto plant = std::make_shared<PlantType>();
                        auto place_pos = grid_buttons[index]->GetButtonPosition();
                        plant->SetPosition(place_pos);
                        plants.push_back(plant);
                        m_Root.AddChild(plant);
                        Setsunnum(-cost);
                        choose = ChoosePlant::NONE;
                        grid_buttons[index]->m_has_plant = true;
                    }
                }
            }
        }
    }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

    State m_CurrentState = State::START;

    Util::Renderer m_Root;
    bool startonce = true;
    std::vector<std::shared_ptr<Zombie>> zombies;  // 多個殭屍
    std::vector<std::shared_ptr<Button>> grid_buttons;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<BackgroundImage> m_store;
    std::shared_ptr<BackgroundImage> m_store_sun;
    std::shared_ptr<BackgroundImage> m_stage1;
    std::vector<std::shared_ptr<Sun>> suns;
    std::vector<std::shared_ptr<BackgroundImage>> storeplants;
    int world_freq = 0;
    //嘗試多個豌豆射手
    std::vector<std::shared_ptr<Peashooter>> peashooters;  // 所有生成的 Peashooter
    std::vector<std::shared_ptr<Pea>> peas;
    std::vector<std::shared_ptr<Plant>> plants;
    Button m_peashooters_button = Button(-564,-490,221,293);
    Button m_sunflower_button = Button(-489,-415,221,293);
    Button m_wallnut_button = Button(-414,-340,221,293);
    Button m_repeater_button = Button(-339,-265,221,293);
    Button m_start_button = Button(28,340,79,155);
    Button m_placeable_button = Button(-435,285,-270,225);
    int sun_num = 0;
    ChoosePlant choose = ChoosePlant::NONE;
};

#endif
