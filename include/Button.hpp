//
// Created by tommy on 2025/3/28.
//

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Util/Input.hpp"

class Button {
public:
    void Setm_has_plant(bool value) {
        m_has_plant = value;
    }
    bool Getm_has_plant() {
        return m_has_plant;
    }
    Button(int min_x, int max_x, int min_y, int max_y) {
        m_min_x = min_x;
        m_max_x = max_x;
        m_min_y = min_y;
        m_max_y = max_y;
        s_ButtonPosition.x = (max_x + min_x)/2 + 10;
        s_ButtonPosition.y = (max_y + min_y)/2;
    }
    bool MouseClickDetect() {
        auto mousePos = Util::Input::GetCursorPosition();
        if(Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            if(mousePos.x <= m_max_x && mousePos.x >= m_min_x && mousePos.y <= m_max_y && mousePos.y >= m_min_y) return true;
        }
        return false;
    }
    glm::vec2 GetButtonPosition() {
        return s_ButtonPosition;
    }



private:
    int m_min_x,m_min_y,m_max_x,m_max_y;
    glm::vec2 s_ButtonPosition;
    bool m_has_plant = false;
};


#endif //BUTTON_HPP
