#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
void App::Start() {
    LOG_TRACE("Start");

    // 生成多個殭屍
    int zombieCount = 5; // 可以調整生成數量
    for (int i = 0; i < zombieCount; ++i) {
        auto zombie = std::make_shared<Zombie>();
        zombie->SetPosition({620 + i * 50, 15});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(zombie);
        m_Root.AddChild(zombie);
    }

    m_Background = std::make_shared<BackgroundImage>();
    m_Root.AddChild(m_Background);


    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

    // if (nor_zombie) {
    //     nor_zombie->Update();
    //     if (nor_zombie->GetDead() && nor_zombie->IfAnimationEnds()) {
    //         nor_zombie->SetPlaying(false);
    //         m_Root.RemoveChild(nor_zombie);
    //         nor_zombie = nullptr;
    //     }
    // }

    for (auto it = zombies.begin(); it != zombies.end();) {
        auto zombie = *it;
        zombie->Update();

        if (zombie->GetDead() && zombie->IfAnimationEnds()) {
            zombie->SetPlaying(false);
            m_Root.RemoveChild(zombie);
            it = zombies.erase(it);  // 移除死亡的殭屍
        } else {
            ++it;
        }
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::End() {
    // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}