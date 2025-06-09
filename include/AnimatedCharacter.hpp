#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"


class AnimatedCharacter : public Util::GameObject {
private:
    bool dead = false;
    int life = 1000;
    int attack_freq = 180; // 3秒
    int attack_value = 2000;
public:
    explicit AnimatedCharacter(const std::vector<std::string>& AnimationPaths);

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }
    void SetPlaying(bool playing) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        if (playing) {
            temp->Play();
        }
    }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetAnimation(const std::vector<std::string>& newAnimationPaths) {
        m_Drawable = std::make_shared<Util::Animation>(newAnimationPaths, false, 150, false, 0);
    }

    void SetAttackvalue(int value) {
        attack_value = value;
    }
    int GetAttackvalue() {
        return attack_value;
    }
    void SetAttackfreq(int value) {
        attack_freq = value;
    }
    int GetAttackfreq() {
        return attack_freq;
    }
    void Setlife(int value) {
        life = value;
    }
    int Getlife() {
        return life;
    }
    // test
    virtual std::array<float, 2> GetSize() const { return {50.0f, 50.0f}; } // 預設寬高
    bool CheckCollisionPea(const std::shared_ptr<AnimatedCharacter>& other) const {
        auto pos1 = GetPosition();
        auto size1 = GetSize();
        auto pos2 = other->GetPosition();
        auto size2 = other->GetSize();
      
        return (pos1[0]  < pos2[0] + (0.2 * size2[0]) &&
                pos1[0]  > pos2[0] - (0.2 * size2[0]) &&
                pos1[1] + (0.5 * size1[1]) < pos2[1] + (0.5 * size2[1]) &&
                pos1[1] - (0.5 * size1[1]) > pos2[1] - (0.5 * size2[1]));

    }
    bool CheckCollisionZombie(const std::shared_ptr<AnimatedCharacter>& other) const {
        auto pos1 = GetPosition();
        auto pos2 = other->GetPosition();
        auto size2 = other->GetSize();

        return (pos1[0]  < pos2[0] + (0.5* size2[0]) &&
                pos1[0]  > pos2[0] - (0.5 * size2[0]) &&
                pos1[1]  < pos2[1] + (0.5 * size2[1]) &&
                pos1[1]  > pos2[1] - (0.5 * size2[1]));

    }
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }
    [[nodiscard]] bool IfAnimationEnds() const;

};

#endif //ANIMATED_CHARACTER_HPP
