#include "Gui/SettingsButton.hpp"

#include "Graphics/Texture.hpp"

#include <iostream>

namespace Gui
{

#define SET_SPRITE_CONDITIONS_AND_DRAW()                                                            \
do                                                                                                  \
{                                                                                                   \
    sprite_.setPosition(topLeft_);                                                                  \
    sprite_.scale((double)width_  / sprite_.getScaleInPixels().x,                                    \
                  (double)height_ / sprite_.getScaleInPixels().y);                                  \
    showing_ = true;                                                                                \
                                                                                                    \
    window.drawSprite(sprite_);                                                                     \
} while (0)

namespace 
{

#define BASIC_LOADER(FILE_NAME)     \
do                                  \               
{   \
    static bool firstLoad = true;   \
    static Graphics::Texture texture;   \
    static Graphics::Sprite sprite;                                                \
    if (firstLoad)         \               
    { \
        firstLoad = false;  \
        texture.loadFromFile(FILE_NAME); \
        sprite.setTexture(texture); \
    }   \
    return sprite;   \
} while(0)

static Graphics::Sprite& loadSpriteNormal()
{
    BASIC_LOADER("media/textures/settingsButtonNormal.png");
}

static Graphics::Sprite& loadSpriteRelease()
{
    BASIC_LOADER("media/textures/settingsButtonRelease.jpeg");
}

static Graphics::Sprite& loadSpriteHover()
{
    BASIC_LOADER("media/textures/settingsButtonHover.png");
}

} // anonymous namespace

SettingsButton::SettingsButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing
) : Button(topLeft, width, height, showing, State::Normal) 
{
    sprite_ = loadSpriteNormal();
    sprite_.setPosition(topLeft_);
    sprite_.scale(width_ / sprite_.getScaleInPixels().x, height_ / sprite_.getScaleInPixels().y);
}

void SettingsButton::onPress(Graphics::Window& window) 
{
    return;
}

void SettingsButton::onRelease(Graphics::Window& window) 
{
    if (state_ == State::Released) 
    {
        state_ = State::Normal;
        sprite_ = loadSpriteHover();
    }
    else
    {                           
        state_ = State::Released;
        sprite_ = loadSpriteRelease();
    }

    SET_SPRITE_CONDITIONS_AND_DRAW();
}

void SettingsButton::onHover(Graphics::Window& window) 
{
    if (state_ != State::Released) 
        sprite_ = loadSpriteHover();
    else 
        sprite_ = loadSpriteRelease();

    SET_SPRITE_CONDITIONS_AND_DRAW(); 
}

void SettingsButton::onUnhover(Graphics::Window& window) 
{   
    switch (state_)
    {
        case State::Released:
            sprite_ = loadSpriteRelease();
            break;
        
        case State::Normal:
            sprite_ = loadSpriteNormal();
            break;

        default: // unreachable
            assert(false);
            break;
    }

    SET_SPRITE_CONDITIONS_AND_DRAW();
}

void SettingsButton::interact(Graphics::Window& window, const Graphics::Event& event)
{
    if (!hovered(window))
    {
        onUnhover(window);
        return;
    }

    switch (event.type)
    {
        case Graphics::Event::EventType::MouseButtonReleased:
            onRelease(window);
            break;
        
        default:
            onHover(window);
            break;
    }
}
} // namespace Gui