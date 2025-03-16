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
    nor_zombie->SetLooping(true);
    nor_zombie->SetPlaying(true);
    auto cur_pos = nor_zombie->GetPosition();
    nor_zombie->SetPosition({cur_pos[0]-0.15, cur_pos[1]});
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