#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "GameContext.hpp"
#include "plant/Cherrybomb.hpp"
#include "plant/Chomper.hpp"
#include "plant/Potatomine.hpp"
#include "plant/Repeater.hpp"
#include "plant/Snowpeashooter.hpp"
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
        polevaultingzombie->SetPosition({520, 0});  // 每隻殭屍的位置稍微錯開
        polevaultingzombie->SetPivot({50,0}); // 圖片偏移
        zombies.push_back(polevaultingzombie);
        m_Root.AddChild(polevaultingzombie);


        // 生成多個殭屍
        int zombieCount = 5; // 可以調整生成數量
        for (int i = 0; i < zombieCount; ++i) {
            auto zombie = std::make_shared<Zombie>();
            zombie->SetPosition({620 + i * 100, 0});  // 每隻殭屍的位置稍微錯開
            zombies.push_back(zombie);
            m_Root.AddChild(zombie);
        }

        // 測試交通錐殭屍
        auto coneheadzombie = std::make_shared<Coneheadzombie>();
        coneheadzombie->SetPosition({1120, 0});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(coneheadzombie);
        m_Root.AddChild(coneheadzombie);

        // 測試鐵桶殭屍
        auto bucketheadzombie = std::make_shared<Bucketheadzombie>();
        bucketheadzombie->SetPosition({1220, 0});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(bucketheadzombie);
        m_Root.AddChild(bucketheadzombie);

        // 測試旗子殭屍
        auto flagzombie = std::make_shared<Flagzombie>();
        flagzombie->SetPosition({1320, 0});  // 每隻殭屍的位置稍微錯開
        zombies.push_back(flagzombie);
        m_Root.AddChild(flagzombie);

        m_store = std::make_shared<BackgroundImage>();
        // m_store->SetBackgroundImage("store");
        // m_store->SetPivot({475,-256});
        m_store->SetBackgroundImage("store_long");
        m_store->SetPivot({350,-256});
        m_store->SetZIndex(-8);
        m_Root.AddChild(m_store);
        m_store_sun = std::make_shared<BackgroundImage>();
        // 太陽花的數量顯示
        m_store_sun->SetBackgroundImage("Sun_num/num_0");
        m_store_sun->SetPivot({603,-227});
        m_store_sun->SetZIndex(-7);
        m_Root.AddChild(m_store_sun);

        // 放入各種植物在商店
        int storeplantCount = 8; // 可以調整生成數量
        for (int i = 0; i < storeplantCount; ++i) {
            auto storeplant = std::make_shared<BackgroundImage>();
            storeplant->SetPivot({537 - i * 57, -256});
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
    // if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
    //     printf("x:%f y:%f\n",Util::Input::GetCursorPosition().x,Util::Input::GetCursorPosition().y);
    // }
    //
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


    //放置植物
    switch (choose) {
        case ChoosePlant::PEASHOOTER:
            PlacePlant<Peashooter>(100);
            break;
        case ChoosePlant::SUNFLOWER:
            PlacePlant<Sunflower>(50);
            break;
        case ChoosePlant::WALLNUT:
            PlacePlant<Wallnut>(50);
            break;
        case ChoosePlant::REPEATER:
            PlacePlant<Repeater>(150);
            break;
        case ChoosePlant::SNOWPEASHOOTER:
            PlacePlant<Snowpeashooter>(150);
            break;
        case ChoosePlant::CHERRYBOMB:
            PlacePlant<Cherrybomb>(200);
            break;
        case ChoosePlant::POTATOMINE:
            PlacePlant<Potatomine>(50);
            break;
        case ChoosePlant::CHOMPER:
            PlacePlant<Chomper>(200);
            break;
    }

    //選擇植物
    ChoosePlant temp_choose = choose;
    if (m_peashooters_button.MouseClickDetect() && Getsunnum()>=100) {
        choose = ChoosePlant::PEASHOOTER;
    }
    if (m_sunflower_button.MouseClickDetect() && Getsunnum()>=50) {
        choose = ChoosePlant::SUNFLOWER;
    }
    if (m_wallnut_button.MouseClickDetect() && Getsunnum()>=50) {
        choose = ChoosePlant::WALLNUT;
    }
    if (m_repeater_button.MouseClickDetect() && Getsunnum()>=150) {
        choose = ChoosePlant::REPEATER;
    }
    if (m_snowpeashooter_button.MouseClickDetect() && Getsunnum()>=150) {
        choose = ChoosePlant::SNOWPEASHOOTER;
    }
    if (m_cherrybomb_button.MouseClickDetect() && Getsunnum()>=200) {
        choose = ChoosePlant::CHERRYBOMB;
    }
    if (m_potatomine_button.MouseClickDetect() && Getsunnum()>=200) {
        choose = ChoosePlant::POTATOMINE;
    }
    if (m_chomper_button.MouseClickDetect() && Getsunnum()>=200) {
        choose = ChoosePlant::CHOMPER;
    }
    if(temp_choose == choose && (m_peashooters_button.MouseClickDetect() || m_sunflower_button.MouseClickDetect() || m_wallnut_button.MouseClickDetect() || m_repeater_button.MouseClickDetect() || m_snowpeashooter_button.MouseClickDetect())) {
        choose = ChoosePlant::NONE;
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

    GameContext ctx{ m_Root, zombies, suns, peas, snowpeas, {}, grid_buttons[1]->GetButtonPosition().x-grid_buttons[0]->GetButtonPosition().x, grid_buttons[9]->GetButtonPosition().y-grid_buttons[0]->GetButtonPosition().y};
    // printf("%.2f %.2f\n",grid_buttons[1]->GetButtonPosition().x-grid_buttons[0]->GetButtonPosition().x, grid_buttons[9]->GetButtonPosition().y-grid_buttons[0]->GetButtonPosition().y);
    // 更新所有植物
    for (auto it = plants.begin(); it != plants.end();) {
        auto plant = *it;
        plant->Update(ctx);
        ++it;
    }
    // 延遲移除 Cherrybomb 等植物
    for (Plant* p : ctx.to_remove_plants) {
        auto it = std::find_if(plants.begin(), plants.end(), [&](std::shared_ptr<Plant>& ptr) {
            return ptr.get() == p;
        });
        if (it != plants.end()) {
            m_Root.RemoveChild(*it);
            plants.erase(it);
        }
    }
    ctx.to_remove_plants.clear();

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

    // 雪豆更新
    for (auto it = snowpeas.begin(); it != snowpeas.end();) {
        auto snowpea = *it;
        snowpea->Update();

        bool hit = false;
        for (auto& zombie : zombies) {
            if (!zombie->GetDead() && snowpea->CheckCollisionPea(zombie)) {
                zombie->Setlife(zombie->Getlife() - 200);
                if (!zombie->Getstartcount()) {
                    zombie->Setstartcount(true);
                }
                zombie->Set_snowpea_shooted(zombie->Get_snowpea_shooted()+1);
                if (zombie->Getlife() <= 0) {
                    zombie->SetDead();
                }
                hit = true;
                break;
            }
        }

        if (snowpea->IsOutOfBounds() || hit) {
            snowpea->SetLooping(false);
            snowpea->SetPlaying(false);
            m_Root.RemoveChild(snowpea);
            it = snowpeas.erase(it);
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