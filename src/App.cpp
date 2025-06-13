#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
#include "plant/Peashooter.hpp"
#include "GameContext.hpp"
#include "Shovel.hpp"
#include "plant/Cherrybomb.hpp"
#include "plant/Chomper.hpp"
#include "plant/Potatomine.hpp"
#include "plant/Repeater.hpp"
#include "plant/Snowpeashooter.hpp"
#include "plant/Sunflower.hpp"
#include "plant/Wallnut.hpp"


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

        m_stagebackground = std::make_shared<BackgroundImage>();
        m_stagebackground->SetBackgroundImage("stage_background");
        m_stagebackground->SetPivot({0,0});
        m_stagebackground->SetZIndex(-1);
        m_Root.AddChild(m_stagebackground);

        m_stage1_3 = std::make_shared<BackgroundImage>();
        m_stage1_3->SetBackgroundImage("stage1_10");
        m_stage1_3->SetPivot({-1600,-220});
        m_stage1_3->SetZIndex(0);
        m_Root.AddChild(m_stage1_3);

        m_CurrentState = State::CHOOSE;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }
    m_Root.Update();

}

void App::Choose() {

    if (Util::Input::IsKeyUp(Util::Keycode::D) && !choosing_r && !choosing_l && move_bound<3) {
        choosing_r = true;
        temp_pivot = m_stage1_3->GetPivot();
        move_bound++;
    }
    else if(Util::Input::IsKeyUp(Util::Keycode::A) && !choosing_l && !choosing_r && move_bound>0) {
        choosing_l = true;
        temp_pivot = m_stage1_3->GetPivot();
        move_bound--;
    }
    if (choosing_r) {
        m_stage1_3->SetPivot({m_stage1_3->GetPivot().x+10,m_stage1_3->GetPivot().y});
    }
    else if (choosing_l) {
        m_stage1_3->SetPivot({m_stage1_3->GetPivot().x-10,m_stage1_3->GetPivot().y});
    }
    if (abs(m_stage1_3->GetPivot().x - temp_pivot.x) >=1360) {
        choosing_r = false;
        choosing_l = false;
    }

    GameContext ctx{
        m_Root, zombies, suns, peas, snowpeas, plants, storeplants, {}, grid_buttons,lawnmowers,
        grid_buttons[1]->GetButtonPosition().x - grid_buttons[0]->GetButtonPosition().x,
        grid_buttons[9]->GetButtonPosition().y - grid_buttons[0]->GetButtonPosition().y,
        button_number
    };

    if (m_left_stage.MouseClickDetect()) {
        stage_to_enter = 1 + move_bound * 3;
        if (stage_to_enter <= max_level_cleared + 1 || cheatmode) {
            printf("Stage%d\n", stage_to_enter);
            SwitchToLevel(stage_to_enter, ctx);
            current_level = stage_to_enter;
            m_Paused = std::make_shared<BackgroundImage>();
            m_Paused->SetBackgroundImage("pause");
            m_Paused->SetPivot({-580,-240});
            m_Paused->SetZIndex(-1);
            m_Root.AddChild(m_Paused);
        } else {
            printf("Stage%d is locked! Clear previous stages first.\n", stage_to_enter);
        }
    }
    if (m_middle_stage.MouseClickDetect()) {
        stage_to_enter = 2 + move_bound * 3;
        if (stage_to_enter <= max_level_cleared + 1 || cheatmode) {
            printf("Stage%d\n", stage_to_enter);
            SwitchToLevel(stage_to_enter, ctx);
            current_level = stage_to_enter;
            m_Paused = std::make_shared<BackgroundImage>();
            m_Paused->SetBackgroundImage("pause");
            m_Paused->SetPivot({-580,-240});
            m_Paused->SetZIndex(-1);
            m_Root.AddChild(m_Paused);
        } else {
            printf("Stage%d is locked! Clear previous stages first.\n", stage_to_enter);
        }
    }
    if (m_right_stage.MouseClickDetect()) {
        stage_to_enter = 3 + move_bound * 3;
        if (stage_to_enter <= max_level_cleared + 1 || cheatmode) {
            printf("Stage%d\n", stage_to_enter);
            SwitchToLevel(stage_to_enter, ctx);
            current_level = stage_to_enter;
            m_Paused = std::make_shared<BackgroundImage>();
            m_Paused->SetBackgroundImage("pause");
            m_Paused->SetPivot({-580,-240});
            m_Paused->SetZIndex(-1);
            m_Root.AddChild(m_Paused);
        } else {
            printf("Stage%d is locked! Clear previous stages first.\n", stage_to_enter);
        }
    }

    // 作弊模式的開關為C
    if (Util::Input::IsKeyUp(Util::Keycode::C)) {
        cheatmode = !cheatmode;
        if (cheatmode) {
            printf("Cheat mode on\n");
        }
        else {
            printf("Cheat mode off\n");
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }

    m_Root.Update();

}


void App::Update() {

    //TODO: do your things here and delete this line <3

    if (paused) {
        m_CurrentState = State::PAUSE;
        pausedpageadded = false;
    }

    if (!paused) {
        if (m_paused_button.MouseClickDetect()) {
            paused = true;
        }
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
            PlacePlant<Potatomine>(125);
            break;
        case ChoosePlant::CHOMPER:
            PlacePlant<Chomper>(200);
            break;
    }
    auto plant = std::make_shared<Sunflower>();
    //選擇植物
    ChoosePlant temp_choose = choose;

    int max_index = std::min(stage_to_enter, 8); // 最多只處理前8個植物
    bool clicked_same_button = false;

    for (int i = 0; i < max_index; ++i) {
        if (m_plant_buttons[i].MouseClickDetect()) {
            if (Getsunnum() >= sun_cost[i]) {
                choose = plant_types[i];
                clicked_same_button = true;
            }
        }
    }

    // 若點擊了同一顆按鈕但沒更換植物，則取消選擇
    if (temp_choose == choose && clicked_same_button) {
        choose = ChoosePlant::NONE;
    }

        GameContext ctx{
            m_Root, zombies, suns, peas, snowpeas, plants, storeplants, {}, grid_buttons,lawnmowers,
            grid_buttons[1]->GetButtonPosition().x - grid_buttons[0]->GetButtonPosition().x,
            grid_buttons[9]->GetButtonPosition().y - grid_buttons[0]->GetButtonPosition().y,
            button_number
        };

        // 更新殭屍
        for (auto it = zombies.begin(); it != zombies.end();) {
            auto zombie = *it;
            zombie->Update(ctx);

            if (zombie->GetDead() && zombie->IfAnimationEnds()) {
                zombie->SetPlaying(false);
                m_Root.RemoveChild(zombie);
                it = zombies.erase(it);  // 移除死亡的殭屍
            }else if(zombie->GetDead() && zombie->Getbeeaten()) {
                zombie->SetPlaying(false);
                m_Root.RemoveChild(zombie);
                it = zombies.erase(it);
            }else {
                ++it;
            }

        }

        // 更新所有植物
        for (auto it = plants.begin(); it != plants.end();) {
            auto plant = *it;
            plant->Update(ctx);
            ++it;
        }
        level.Update(ctx);



        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && shovel->GetClick()) {
            shovel->Clean(ctx,Util::Input::GetCursorPosition());
            shovel->SetClick();
        }
        if (m_shovel.MouseClickDetect()) {
            shovel->SetClick();
        }


        // 延遲移除死亡植物
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
                if (!zombie->GetDead() && pea->CheckCollisionPea(zombie) && zombie->Getontheground()) {
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
                if (!zombie->GetDead() && snowpea->CheckCollisionPea(zombie) && zombie->Getontheground()) {
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
        // 作弊模式的開關為C
        if (Util::Input::IsKeyUp(Util::Keycode::C)) {
            cheatmode = !cheatmode;
            if (cheatmode) {
                printf("Cheat mode on\n");
            }
            else {
                printf("Cheat mode off\n");
            }
        }
        // 作弊模式下太陽數量始終為200
        if (cheatmode) {
            int addnum = 200 - Getsunnum();
            Setsunnum(addnum);
        }

        // 更新太陽數量的顯示
        int temp_sunnumber = Getsunnum();
        for(int i = 0; i < 5;i++) {
            int temp_number = temp_sunnumber % 10;
            temp_sunnumber = temp_sunnumber / 10;
            m_store_suns[i]->SetBackgroundImage("Sun_num/digit_"+std::to_string(temp_number));
        }


        // 如果zombies空了的話，就判定關卡結束
        if (zombies.size() == 0) {

            m_CurrentState = State::CHOOSE;

            // 更新破關進度
            if (!cheatmode && current_level > max_level_cleared) {
                max_level_cleared = current_level;
            }

            // TODO: 把所有植物、豌豆、背景erase掉
            clearall();
            m_Root.RemoveChild(m_Paused);
        }
        else {
            for (auto zombie : zombies) {
                auto xy = zombie->GetPosition();
                if(xy.x < -625) {
                    m_CurrentState = State::CHOOSE;
                    clearall();
                    m_Root.RemoveChild(m_Paused);
                    break;
                }
            }
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
void App::Pause() {
    //加一次就好
    if (!pausedpageadded) {
        m_Pausedpage = std::make_shared<BackgroundImage>();
        m_Pausedpage->SetBackgroundImage("Setting");
        m_Pausedpage->SetPivot({0,0});
        m_Pausedpage->SetZIndex(10);
        m_Root.AddChild(m_Pausedpage);

        // 暫停殭屍
        for (auto it = zombies.begin(); it != zombies.end();) {
            auto zombie = *it;
            zombie->SetPlaying(false);
            zombie->SetLooping(false);
            ++it;
        }

        // 暫停所有植物
        for (auto it = plants.begin(); it != plants.end();) {
            auto plant = *it;
            plant->SetPlaying(false);
            plant->SetLooping(false);
            ++it;
        }

        // 豌豆暫停
        for (auto it = peas.begin(); it != peas.end();) {
            auto pea = *it;
            pea->SetPlaying(false);
            pea->SetLooping(false);
            ++it;
        }

        // 雪豆暫停
        for (auto it = snowpeas.begin(); it != snowpeas.end();) {
            auto snowpea = *it;
            snowpea->SetPlaying(false);
            snowpea->SetLooping(false);
            ++it;
        }

        // 太陽暫停
        for (auto it = suns.begin(); it != suns.end();) {
            auto sun = *it;
            sun->SetPlaying(false);
            sun->SetLooping(false);
            ++it;
        }
        pausedpageadded = true;
    }


    if (m_menu_button.MouseClickDetect()) {
        clearall();
        m_CurrentState = State::CHOOSE;
        m_Root.RemoveChild(m_Pausedpage);
        m_Root.RemoveChild(m_Paused);
        paused = false;
    }
    else if (m_continue_button.MouseClickDetect()) {
        // 恢復殭屍
        for (auto it = zombies.begin(); it != zombies.end();) {
            auto zombie = *it;
            zombie->SetPlaying(true);
            zombie->SetLooping(true);
            ++it;
        }

        // 恢復所有植物
        for (auto it = plants.begin(); it != plants.end();) {
            auto plant = *it;
            plant->SetPlaying(true);
            plant->SetLooping(true);
            ++it;
        }

        // 恢復豌豆
        for (auto it = peas.begin(); it != peas.end();) {
            auto pea = *it;
            pea->SetPlaying(true);
            pea->SetLooping(true);
            ++it;
        }

        // 恢復雪豆
        for (auto it = snowpeas.begin(); it != snowpeas.end();) {
            auto snowpea = *it;
            snowpea->SetPlaying(true);
            snowpea->SetLooping(true);
            ++it;
        }

        // 恢復太陽
        for (auto it = suns.begin(); it != suns.end();) {
            auto sun = *it;
            sun->SetPlaying(true);
            sun->SetLooping(true);
            ++it;
        }
        m_CurrentState = State::UPDATE;
        m_Root.RemoveChild(m_Pausedpage);
        paused = false;
    }
    else if (m_restart_button.MouseClickDetect()) {
        clearall();
        GameContext ctx{
            m_Root, zombies, suns, peas, snowpeas, plants, storeplants, {}, grid_buttons,lawnmowers,
            grid_buttons[1]->GetButtonPosition().x - grid_buttons[0]->GetButtonPosition().x,
            grid_buttons[9]->GetButtonPosition().y - grid_buttons[0]->GetButtonPosition().y,
            button_number
        };
        m_CurrentState = State::UPDATE;
        SwitchToLevel(stage_to_enter,ctx);
        m_Root.RemoveChild(m_Pausedpage);
        paused = false;
        Resetsunnum();
    }

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