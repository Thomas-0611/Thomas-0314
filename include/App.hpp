#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "AnimatedCharacter.hpp"
#include "zombie/Zombie.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "Util/Renderer.hpp"


class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;

    Util::Renderer m_Root;

    std::vector<std::shared_ptr<Zombie>> zombies;  // 多個殭屍
    // std::shared_ptr<Peashooter> m_peashooter;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<BackgroundImage> m_store;
    std::vector<std::shared_ptr<BackgroundImage>> storeplants;

    //嘗試多個豌豆射手
    std::vector<std::shared_ptr<Peashooter>> peashooters;  // 所有生成的 Peashooter
    int nextPeashooterX = -200; // 初始位置
};

#endif
