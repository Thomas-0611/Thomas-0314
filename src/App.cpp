#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "GameContext.hpp"
#include "plant/Repeater.hpp"
#include "plant/Sunflower.hpp"
#include "plant/Wallnut.hpp"
#include "zombie/Coneheadzombie.hpp"
#include "zombie/Bucketheadzombie.hpp"
#include "zombie/Flagzombie.hpp"
#include "zombie/Polevaultingzombie.hpp"

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
        // 測試撐竿跳殭屍
        auto polevaultingzombie = std::make_shared<Polevaultingzombie>();
        polevaultingzombie->SetPosition({520, 15});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(polevaultingzombie);
        m_Root.AddChild(polevaultingzombie);


        // 生成多個殭屍
        int zombieCount = 5; // 可以調整生成數量
        for (int i = 0; i < zombieCount; ++i) {
            auto zombie = std::make_shared<Zombie>();
            zombie->SetPosition({620 + i * 100, 15});  // 每隻殭屍的位置稍微錯開
            zombies.push_back(zombie);
            m_Root.AddChild(zombie);
        }

        // 測試交通錐殭屍
        auto coneheadzombie = std::make_shared<Coneheadzombie>();
        coneheadzombie->SetPosition({1120, 15});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(coneheadzombie);
        m_Root.AddChild(coneheadzombie);

        // 測試鐵桶殭屍
        auto bucketheadzombie = std::make_shared<Bucketheadzombie>();
        bucketheadzombie->SetPosition({1220, 15});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(bucketheadzombie);
        m_Root.AddChild(bucketheadzombie);

        // 測試旗子殭屍
        auto flagzombie = std::make_shared<Flagzombie>();
        flagzombie->SetPosition({1320, 15});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(flagzombie);
        m_Root.AddChild(flagzombie);

        m_store = std::make_shared<BackgroundImage>();
        m_store->SetBackgroundImage("store");
        m_store->SetPivot({475,-256});
        m_store->SetZIndex(-8);
        m_Root.AddChild(m_store);
        m_store_sun = std::make_shared<BackgroundImage>();
        // 太陽花的數量顯示
        m_store_sun->SetBackgroundImage("Sun_num/num_0");
        m_store_sun->SetPivot({603,-227});
        m_store_sun->SetZIndex(-7);
        m_Root.AddChild(m_store_sun);

        // 放入各種植物在商店
        int storeplantCount = 4; // 可以調整生成數量
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
    // printf("x:%f y:%f\n",Util::Input::GetCursorPosition().x,Util::Input::GetCursorPosition().y);
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
    // if (GetClick() && Getsunnum()>=100) {
    //     if (m_placeable_button.MouseClickDetect()) {
    //         auto m_peashooter = std::make_shared<Peashooter>();
    //         auto place_pos = Util::Input::GetCursorPosition();
    //         m_peashooter->SetPosition(place_pos);
    //         plants.push_back(m_peashooter);
    //         m_Root.AddChild(m_peashooter);
    //         Setsunnum(-100);
    //         SetClick();
    //     }
    // }


    for (int i = 0;i < 9;i++) {
        for(int j = 0;j < 5;j++) {
            if(grid_buttons[9*j+i]->MouseClickDetect() && grid_buttons[9*j+i]->m_has_plant == false && Getsunnum()>100) {
                auto m_peashooter = std::make_shared<Peashooter>();
                auto place_pos = grid_buttons[9*j+i]->GetButtonPosition();
                m_peashooter->SetPosition(place_pos);
                plants.push_back(m_peashooter);
                m_Root.AddChild(m_peashooter);
                Setsunnum(-100);
                SetClick();
                grid_buttons[9*j+i]->m_has_plant = true;
            }
        }
    }

    // 生成太陽花
    if (GetSunflowerClick() && Getsunnum()>=50) {
        if (m_placeable_button.MouseClickDetect()) {
            auto m_sunflower = std::make_shared<Sunflower>();
            auto place_pos = Util::Input::GetCursorPosition();
            m_sunflower->SetPosition(place_pos);
            plants.push_back(m_sunflower);
            m_Root.AddChild(m_sunflower);
            Setsunnum(-50);
            SetSunflowerClick();
        }
    }

    // 生成堅果牆
    if (GetWallnutClick() && Getsunnum()>=50) {
        if (m_placeable_button.MouseClickDetect()) {
            auto m_wallnut = std::make_shared<Wallnut>();
            auto place_pos = Util::Input::GetCursorPosition();
            m_wallnut->SetPosition(place_pos);
            plants.push_back(m_wallnut);
            m_Root.AddChild(m_wallnut);
            Setsunnum(-50);
            SetWallnutClick();
        }
    }

    // 生成連發豌豆
    if (GetRepeaterClick() && Getsunnum()>=150) {
        if (m_placeable_button.MouseClickDetect()) {
            auto m_repeater = std::make_shared<Repeater>();
            auto place_pos = Util::Input::GetCursorPosition();
            m_repeater->SetPosition(place_pos);
            plants.push_back(m_repeater);
            m_Root.AddChild(m_repeater);
            Setsunnum(-150);
            SetRepeaterClick();
        }
    }

    if (m_peashooters_button.MouseClickDetect() && Getsunnum()>=100) {
        if (GetSunflowerClick()) {
            SetSunflowerClick();
        }
        if (GetWallnutClick()) {
            SetWallnutClick();
        }
        if (GetRepeaterClick()) {
            SetRepeaterClick();
        }
        SetClick();
    }
    if (m_sunflower_button.MouseClickDetect() && Getsunnum()>=50) {
        if (GetClick()) {
            SetClick();
        }
        if (GetWallnutClick()) {
            SetWallnutClick();
        }
        if (GetRepeaterClick()) {
            SetRepeaterClick();
        }
        SetSunflowerClick();
    }
    if (m_wallnut_button.MouseClickDetect() && Getsunnum()>=50) {
        if (GetClick()) {
            SetClick();
        }
        if (GetSunflowerClick()) {
            SetSunflowerClick();
        }
        if (GetRepeaterClick()) {
            SetRepeaterClick();
        }
        SetWallnutClick();
    }
    if (m_repeater_button.MouseClickDetect() && Getsunnum()>=150) {
        if (GetClick()) {
            SetClick();
        }
        if (GetSunflowerClick()) {
            SetSunflowerClick();
        }
        if (GetWallnutClick()) {
            SetWallnutClick();
        }
        SetRepeaterClick();
    }

    // 更新殭屍
    for (auto it = zombies.begin(); it != zombies.end();) {
        auto zombie = *it;
        zombie->Update(m_Root,plants);

        if (zombie->GetDead() && zombie->IfAnimationEnds()) {
            zombie->SetPlaying(false);
            m_Root.RemoveChild(zombie);
            it = zombies.erase(it);  // 移除死亡的殭屍
        } else {
            ++it;
        }
    }

    GameContext ctx{ m_Root, zombies, suns, peas };
    // 更新所有植物
    for (auto it = plants.begin(); it != plants.end();) {
        auto plant = *it;
        plant->Update(ctx);
        ++it;
    }

    // 豌豆更新
    for (auto it = peas.begin(); it != peas.end();) {
        auto pea = *it;
        pea->Update();

        bool hit = false;
        for (auto& zombie : zombies) {
            if (!zombie->GetDead() && pea->CheckCollisionPea(zombie)) {
                zombie->Setlife(zombie->Getlife() - 200);
                if (zombie->Getlife() <= 0) {
                    zombie->SetDead();
                }
                hit = true;
                break;
            }
        }

        if (pea->IsOutOfBounds() || hit) {
            pea->SetLooping(false);
            pea->SetPlaying(false);
            m_Root.RemoveChild(pea);
            it = peas.erase(it);
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
            Setsunnum(25);
        }
        else {
            ++it;
        }
    }

    // 更新太陽數量的顯示
    m_store_sun->SetBackgroundImage("Sun_num/num_"+std::to_string(Getsunnum()));

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