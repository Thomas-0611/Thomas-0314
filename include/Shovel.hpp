//
// Created by Thomas on 2025/5/23.
//

#ifndef SHOVEL_HPP
#define SHOVEL_HPP
#include "AnimatedCharacter.hpp"
#include "GameContext.hpp"

class Shovel : public AnimatedCharacter {
public:
    Shovel();
    void Clean(GameContext& ctx,glm::vec2 pos);
    virtual ~Shovel() = default;
    void SetClick() {
        Clicked = !Clicked;
    }
    bool GetClick() {
        return Clicked;
    }
private:
    bool Clicked = false;
};
#endif //SHOVEL_HPP
