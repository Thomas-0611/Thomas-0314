#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "AnimatedCharacter.hpp"
#include "zombie/Zombie.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "Util/Renderer.hpp"
#include "Button.hpp"


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
    std::shared_ptr<BackgroundImage> m_stage1;

    std::vector<std::shared_ptr<BackgroundImage>> storeplants;

    //嘗試多個豌豆射手
    std::vector<std::shared_ptr<Peashooter>> peashooters;  // 所有生成的 Peashooter
    Button m_peashooters_button = Button(-564,-490,221,293);
    Button m_start_button = Button(28,340,79,155);
    Button m_placeable_button = Button(-435,285,-270,225);
    bool pick = false;
};

#endif
