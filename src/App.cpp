#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"


void App::Start() {
    LOG_TRACE("Start");
    int grid_xmin = -461;
    int grid_xmax = 285;
    int grid_ymin = -267;
    int grid_ymax = 220;
    float grid_x = (grid_xmax - grid_xmin)/9;
    float grid_y = (grid_ymax - grid_ymin)/5;
    for(int row = 0;row < 5;row++) {
        for(int column = 0;column < 9;column++) {
            grid_buttons.push_back(std::make_shared<Button>(round(grid_xmin+grid_x*column), round(grid_xmin+grid_x*(column+1)), round(grid_ymin+grid_y*row), round(grid_ymin+grid_y*(row+1))));
        }
    }
    // 開始畫面
    if (startonce) {
        m_Background = std::make_shared<BackgroundImage>();
        m_Root.AddChild(m_Background);
        Setstartonce();
    }

    // 如果點在範圍內(開始遊戲的按鈕)
    if (m_start_button.MouseClickDetect()) {
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
        m_stage1->SetBackgroundImage("five");
        m_stage1->SetZIndex(-9);
        m_Root.AddChild(m_stage1);
        m_CurrentState = State::UPDATE;
    }
    m_Root.Update();

}

void App::Update() {
    printf("x:%f y:%f\n",Util::Input::GetCursorPosition().x,Util::Input::GetCursorPosition().y);
    //TODO: do your things here and delete this line <3
    if (Getworldfreq()>540) {
        //生成太陽
        auto m_Sun = std::make_shared<Sun>();
        suns.push_back(m_Sun);
        m_Root.AddChild(m_Sun);
        Setworldfreq(0);
    }
    else {
        Setworldfreq(Getworldfreq()+1);
    }

    // 按下F1，生成一隻豌豆射手
    /*
    if (GetClick() && Getsunnum()>1) {
        if (m_placeable_button.MouseClickDetect()) {
            auto m_peashooter = std::make_shared<Peashooter>();
            auto place_pos = Util::Input::GetCursorPosition();
            m_peashooter->SetPosition(place_pos);
            peashooters.push_back(m_peashooter);
            m_Root.AddChild(m_peashooter);
            Setsunnum(-1);
            SetClick();
        }
    }
    */

    for (int i = 0;i < 9;i++) {
        for(int j = 0;j < 5;j++) {
            if(grid_buttons[9*j+i]->MouseClickDetect() && grid_buttons[9*j+i]->m_has_plant == false && Getsunnum()>1) {
                auto m_peashooter = std::make_shared<Peashooter>();
                auto place_pos = grid_buttons[9*j+i]->GetButtonPosition();
                m_peashooter->SetPosition(place_pos);
                peashooters.push_back(m_peashooter);
                m_Root.AddChild(m_peashooter);
                Setsunnum(-1);
                SetClick();
                grid_buttons[9*j+i]->m_has_plant = true;
            }
        }
    }

    if (m_peashooters_button.MouseClickDetect()) {
        SetClick();
    }

    for (auto& shooter : peashooters) {
        m_Root = shooter->Update(m_Root,zombies);
    }
    // 更新殭屍
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

    // 更新太陽
    for (auto it = suns.begin(); it != suns.end();) {
        auto sun = *it;
        sun->Update();
        if (sun->GetPick()) {
            m_Root.RemoveChild(sun);
            it = suns.erase(it);
            Setsunnum(1);
        }
        else {
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