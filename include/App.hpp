#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "AnimatedCharacter.hpp"
#include "Zombie.hpp"
#include "BackgroundImage.hpp"
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

    std::shared_ptr<BackgroundImage> m_Background;
};

#endif
