#include "Gui/SettingsButton.hpp"

#include "Graphics/Texture.hpp"

#include <iostream>

namespace Gui
{

void SettingsButton::tmp(const char* textureFileName)
{
    texture_.loadFromFile(textureFileName);

    sprite_.setTexture(texture_);
    showing_ = true;
}

void SettingsButton::onPress(Graphics::Window& window) 
{
    tmp("media/textures/tmp1.png");

    std::cout << "press\n";
}

void SettingsButton::onRelease(Graphics::Window& window) 
{
    tmp("media/textures/tmp2.jpeg");
    
    if (state_ == State::Released) state_ = State::Normal;
    else                           state_ = State::Released;

    std::cout << "release\n";
}
void SettingsButton::onHover(Graphics::Window& window) 
{
    tmp("media/textures/tmp3.jpeg");

    //std::cout << "hover\n";
}

void SettingsButton::onUnhover(Graphics::Window& window) 
{
    if (state_ != State::Released)
        tmp("media/textures/tmp4.png");
}

} // namespace Gui