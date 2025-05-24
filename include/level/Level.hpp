//
// Created by tommy on 2025/5/8.
//

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "ZombieSpawner.hpp"
#include "Lawnmower.hpp"

class Level {
public:
    Level() = default;

    virtual void Load(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies, std::vector<std::shared_ptr<BackgroundImage>>& storeplants, int& button_number, std::vector<std::shared_ptr<Lawnmower>>& lawnmowers) = 0;
    virtual void GameUpdate(Util::Renderer& root,std::vector<std::shared_ptr<Zombie>>& zombies,GameContext& ctx, std::vector<std::shared_ptr<Lawnmower>>& lawnmowers) = 0;
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
