//
// Created by Thomas on 2025/3/21.
//
#include "plant/Peashooter.hpp"

Peashooter::Peashooter()
    : AnimatedCharacter(std::vector<std::string>()) { // 初始化父類
    std::vector<std::string> peashooterImages;
    for (int i = 0; i < 13; ++i) {
        peashooterImages.emplace_back(RESOURCE_DIR"/Day/Plant/Peashooter/frame_" + std::to_string(i) + "_delay-0.09s.png");
    }
    SetAnimation(peashooterImages);
    SetZIndex(2);
    SetPosition({-120, 0});
    SetVisible(true);
    Setlife(1500);
    SetAttackfreq(180);
    SetAttackvalue(200);
}

Util::Renderer Peashooter::Update(Util::Renderer m_Root) {
    if (!m_dead) {
        SetLooping(true);
        SetPlaying(true);

        int freq = GetAttackfreq();
        if (cur_freq >= freq) {
            //TODO:射出豌豆
            std::vector<std::string> peaImages;
            peaImages.emplace_back(RESOURCE_DIR"/Day/Plant/pea/pea.png");

            auto pea = std::make_shared<Pea>(peaImages, GetPosition()[0], GetPosition()[1]);
            peas.push_back(pea);
            m_Root.AddChild(pea);
            printf("shoot\n");
            Setcurfreq(0);
        }
        else {
            Setcurfreq(cur_freq+1);
        }

        // 檢查並移除超出範圍的豌豆
        for (auto it = peas.begin(); it != peas.end();) {
            auto pea = *it;
            pea->Update();
            if (pea->IsOutOfBounds()) {
                pea->SetLooping(false);
                pea->SetPlaying(false);
                m_Root.RemoveChild(pea);  // 移除超出範圍的豌豆
                it = peas.erase(it);
            } else {
                ++it;
            }
        }

    }
    return m_Root;
}

void Peashooter::SetDead() {
    if (!m_dead) {
        m_dead = true;
        std::vector<std::string> zombiedeadImages;
        for (int i = 0; i < 10; ++i) {
            zombiedeadImages.emplace_back(RESOURCE_DIR"/Day/Zombie/Zombie(dead)/frame_" + std::to_string(i) + "_delay-0.1s.png");
        }
        SetAnimation(zombiedeadImages);
        SetLooping(false);
        SetPlaying(true);
    }
}