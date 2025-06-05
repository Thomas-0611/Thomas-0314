    //
    // Created by Thomas on 2025/5/7.
    //

    #ifndef LAWNMOWER_HPP
    #define LAWNMOWER_HPP
    #include "AnimatedCharacter.hpp"
    #include "GameContext.hpp"

    class Lawnmower : public AnimatedCharacter {
    public:
        Lawnmower(int index);
        void Update(GameContext& ctx);
        bool GetDead() const { return m_dead; }
        void SetDead() {
            if (!m_dead) {
                m_dead = true;
                SetLooping(false);
                SetPlaying(false);
                SetVisible(false);
            }
        };
        bool Getcleaning() {
            return cleaning;
        }
        void Cleanall(GameContext& ctx);
        virtual ~Lawnmower() = default;
    private:
        bool m_dead = false;
        bool cleaning = false;
        int m_index;
    };

    #endif //LAWNMOWER_HPP
