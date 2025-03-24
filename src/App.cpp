#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"

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

    m_peashooter = std::make_shared<Peashooter>();
    m_Root.AddChild(m_peashooter);
    m_Background = std::make_shared<BackgroundImage>();
    m_Root.AddChild(m_Background);
    m_store = std::make_shared<BackgroundImage>();
    m_store->SetBackgroundImage("store");
    m_store->SetPivot({475,-256});
    m_store->SetZIndex(-9);
    m_Root.AddChild(m_store);
    // 放入各種植物在商店
    int storeplantCount = 2; // 可以調整生成數量
    for (int i = 0; i < storeplantCount; ++i) {
        auto storeplant = std::make_shared<BackgroundImage>();
        storeplant->SetPivot({460 + i * 70, -256});  // 每隻殭屍的位置稍微錯開
        storeplant->SetZIndex(-8);
        storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
        storeplants.push_back(storeplant);
        m_Root.AddChild(storeplant);
    }

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

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
    m_Root = m_peashooter->Update(m_Root);


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