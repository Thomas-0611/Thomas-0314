#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"

void App::Start() {
    LOG_TRACE("Start");

    // 開始畫面
    if (startonce) {
        m_Background = std::make_shared<BackgroundImage>();
        m_Root.AddChild(m_Background);
        Setstartonce();
    }

    // 如果點在範圍內(開始遊戲的按鈕)
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        auto mouse_pos = Util::Input::GetCursorPosition();
        if (mouse_pos.x >= 28 && mouse_pos.x <= 340 && mouse_pos.y >= 79 && mouse_pos.y <= 155) {
            // 生成多個殭屍
            int zombieCount = 5; // 可以調整生成數量
            for (int i = 0; i < zombieCount; ++i) {
                auto zombie = std::make_shared<Zombie>();
                zombie->SetPosition({620 + i * 50, 15});  // 每隻殭屍的位置稍微錯開
                zombies.push_back(zombie);
                m_Root.AddChild(zombie);
            }
            m_store = std::make_shared<BackgroundImage>();
            m_store->SetBackgroundImage("store");
            m_store->SetPivot({475,-256});
            m_store->SetZIndex(-8);
            m_Root.AddChild(m_store);

            // 放入各種植物在商店
            int storeplantCount = 2; // 可以調整生成數量
            for (int i = 0; i < storeplantCount; ++i) {
                auto storeplant = std::make_shared<BackgroundImage>();
                storeplant->SetPivot({525 - i * 75, -256});
                storeplant->SetZIndex(-7);
                storeplant->SetBackgroundImage("plant"+std::to_string(i+1));
                storeplants.push_back(storeplant);
                m_Root.AddChild(storeplant);
            }
            m_stage1 = std::make_shared<BackgroundImage>();
            m_stage1->SetBackgroundImage("one");
            m_stage1->SetZIndex(-9);
            m_Root.AddChild(m_stage1);
            m_CurrentState = State::UPDATE;
        }
    }
    m_Root.Update();
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

    // 按下F1，生成一隻豌豆射手
    if (GetClick()) {
        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            auto place_pos = Util::Input::GetCursorPosition();
            if (place_pos.x >= -435 && place_pos.x <= 285 && place_pos.y >= -270 && place_pos.y <= 225) {
                auto m_peashooter = std::make_shared<Peashooter>();
                m_peashooter->SetPosition(place_pos);
                peashooters.push_back(m_peashooter);
                m_Root.AddChild(m_peashooter);
            }
        }
    }

    auto mouse_pos = Util::Input::GetCursorPosition();
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && mouse_pos.x >= -565 && mouse_pos.x <= -488 && mouse_pos.y >= 222 && mouse_pos.y <= 292) {
        SetClick();
    }

    for (auto& shooter : peashooters) {
        m_Root = shooter->Update(m_Root,zombies);
    }

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