#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR"/Background/start.png"), -10) {
    }

    void SetBackgroundImage(std::string path) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(ImagePath(path));
    }

private:
    inline std::string ImagePath(std::string path) {
        return RESOURCE_DIR"/Background/" + path + ".png";
    }
};

#endif //BACKGROUND_IMAGE_HPP
