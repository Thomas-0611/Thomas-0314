//
// Created by tommy on 2025/5/8.
//

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "ZombieSpawner.hpp"

class Level {
public:
    Level() = default;

    virtual void Load(GameContext& ctx) = 0;
    virtual void GameUpdate(GameContext& ctx) = 0;
    void RemoveStage(Util::Renderer& root) {
        if (m_stage) {
            root.RemoveChild(m_stage);
            m_stage = nullptr;
        }
    }
protected:
    std::shared_ptr<BackgroundImage> m_stage = nullptr;

};

#endif //LEVEL_HPP
