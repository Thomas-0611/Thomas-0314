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

    State GetCurrentState() const { return m_CurrentState; }
    void Setstartonce() {
        startonce = false;
    }
    void SetClick() {
        pick = !pick;
    }
    bool GetClick() {
        return pick;
    }
    void SetSunflowerClick() {
        sunflower_pick = !sunflower_pick;
    }
    bool GetSunflowerClick() {
        return sunflower_pick;
    }
    void SetWallnutClick() {
        wallnut_pick = !wallnut_pick;
    }
    bool GetWallnutClick() {
        return wallnut_pick;
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

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

    State m_CurrentState = State::START;

    Util::Renderer m_Root;
    bool startonce = true;
    std::vector<std::shared_ptr<Zombie>> zombies;  // 多個殭屍
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
    Button m_start_button = Button(28,340,79,155);
    Button m_placeable_button = Button(-435,285,-270,225);
    bool pick = false;
    bool sunflower_pick = false;
    bool wallnut_pick = false;
    int sun_num = 0;
};

#endif
