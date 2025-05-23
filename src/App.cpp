#include "App.hpp"

#include "Util/Image.hpp"
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

    if (m_left_stage.MouseClickDetect()) {
        if (move_bound == 0) {
            printf("Stage1\n");
            SwitchToLevel(1);

        }
        else if (move_bound == 1) {
            printf("Stage4\n");
            SwitchToLevel(4);
        }
        else if (move_bound == 2) {
            printf("Stage7\n");
            SwitchToLevel(7);
        }
        else if (move_bound == 3) {
            printf("Stage10\n");
            SwitchToLevel(10);
        }
        shovel = std::make_shared<Shovel>();
        m_Root.AddChild(shovel);
    }
    if (m_middle_stage.MouseClickDetect()) {
        if (move_bound == 0) {
            printf("Stage2\n");
            SwitchToLevel(2);
        }
        else if (move_bound == 1) {
            printf("Stage5\n");
            SwitchToLevel(5);
        }
        else if (move_bound == 2) {
            printf("Stage8\n");
            SwitchToLevel(8);
        }
        shovel = std::make_shared<Shovel>();
        m_Root.AddChild(shovel);
    }
    if (m_right_stage.MouseClickDetect()) {
        if (move_bound == 0) {
            printf("Stage3\n");
            SwitchToLevel(3);
        }
        else if (move_bound == 1) {
            printf("Stage6\n");
            SwitchToLevel(6);
        }
        else if (move_bound == 2) {
            printf("Stage9\n");
            SwitchToLevel(9);
        }
        shovel = std::make_shared<Shovel>();
        m_Root.AddChild(shovel);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }
    m_Root.Update();
}


void App::Update() {

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
    auto plant = std::make_shared<Sunflower>();
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
        }else if(zombie->GetDead() && zombie->Getbeeaten()) {
            zombie->SetPlaying(false);
            m_Root.RemoveChild(zombie);
            it = zombies.erase(it);
        }else {
            ++it;
        }

    }

    GameContext ctx{ m_Root, zombies, suns, peas, snowpeas, plants,{}, grid_buttons, grid_buttons[1]->GetButtonPosition().x-grid_buttons[0]->GetButtonPosition().x, grid_buttons[9]->GetButtonPosition().y-grid_buttons[0]->GetButtonPosition().y};
    // printf("%.2f %.2f\n",grid_buttons[1]->GetButtonPosition().x-grid_buttons[0]->GetButtonPosition().x, grid_buttons[9]->GetButtonPosition().y-grid_buttons[0]->GetButtonPosition().y);
    // 更新所有植物
    for (auto it = plants.begin(); it != plants.end();) {
        auto plant = *it;
        plant->Update(ctx);
        ++it;
    }
    //lawnmower->Update(ctx);
    level.Update(m_Root, zombies,ctx,lawnmowers);



    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && shovel->GetClick()) {
        printf("clean the plant\n");
        shovel->Clean(ctx,Util::Input::GetCursorPosition());
        shovel->SetClick();
    }
    if (m_shovel.MouseClickDetect()) {
        printf("I'm here\n");
        shovel->SetClick();
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


    // 更新太陽數量的顯示
    int temp_sunnumber = Getsunnum();
    for(int i = 0; i < 5;i++) {
        int temp_number = temp_sunnumber % 10;
        temp_sunnumber = temp_sunnumber / 10;
        m_store_suns[i]->SetBackgroundImage("Sun_num/digit_"+std::to_string(temp_number));
    }
    //m_store_sun->SetBackgroundImage("Sun_num/num_"+std::to_string(Getsunnum()));
    // 這裡要修


    // 如果zombies空了的話，就判定關卡結束
    if (zombies.size() == 0) {
        m_stage1_3->SetZIndex(0);
        m_stagebackground->SetZIndex(-1);
        m_CurrentState = State::CHOOSE;
        // TODO: 把所有植物、豌豆、背景erase掉
        clearall();

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