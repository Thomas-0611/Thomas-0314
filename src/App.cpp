#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "BackgroundImage.hpp"
void App::Start() {
    LOG_TRACE("Start");


    std::vector<std::string> zombieImages;
    zombieImages.reserve(2);
    for (int i = 0; i < 18; ++i) {
        zombieImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(walk)/frame_" + std::to_string(i) + "_delay-0.2s.png");
    }

    nor_zombie = std::make_shared<AnimatedCharacter>(zombieImages);
    nor_zombie->SetZIndex(2);
    nor_zombie->SetPosition({620,15});
    nor_zombie->SetVisible(true);
    m_Root.AddChild(nor_zombie);

    m_Background = std::make_shared<BackgroundImage>();
    m_Root.AddChild(m_Background);


    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    if (!nor_zombie->Getzombiedead()) {
        nor_zombie->SetLooping(true);
        nor_zombie->SetPlaying(true);
    }
    auto cur_pos = nor_zombie->GetPosition();
    if (!nor_zombie->Getzombiedead()) {
        nor_zombie->SetPosition({cur_pos[0]-0.15, cur_pos[1]});
    }


    // testing dead
    if (cur_pos[0] <= 600 && !nor_zombie->Getzombiedead()) {
        nor_zombie->Setdead();
        std::vector<std::string> zombiedeadImages;
        zombiedeadImages.reserve(2);
        for (int i = 0; i < 10; ++i) {
            zombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        // 切換動畫
        nor_zombie->SetAnimation(zombiedeadImages);
        nor_zombie->SetLooping(false);  // 只播放一次
        nor_zombie->SetPlaying(true);
    }

    if (nor_zombie->Getzombiedead() && nor_zombie->IfAnimationEnds()){
        nor_zombie->SetPlaying(false);
        m_Root.RemoveChild(nor_zombie);
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