#include "Gui/SettingsButton.hpp"

#include "Graphics/Texture.hpp"

#include <iostream>

namespace Gui
{

#define SET_SPRITE_CONDITIONS_AND_DRAW()                                                            \
do                                                                                                  \
{                                                                                                   \
    sprite_.setPosition(topLeft_);                                                                  \
    sprite_.scaleInPixels({width_, height_});                                                       \
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

Graphics::Sprite& loadSpriteNormal()
{
    BASIC_LOADER("media/textures/settingsButtonNormal.png");
}

Graphics::Sprite& loadSpriteRelease()
{
    BASIC_LOADER("media/textures/settingsButtonRelease.jpeg");
}

Graphics::Sprite& loadSpriteHover()
{
    BASIC_LOADER("media/textures/settingsButtonHover.png");
}

#undef BASIC_LOADER

void doReleaseAction(
    Graphics::Window& window, Graphics::Sprite& spriteToChange, 
    ButtonsArray& buttons, const Graphics::Event& event
)
{
    spriteToChange = loadSpriteRelease();   

    buttons.drawButtons(window);
    buttons.interactWithButtons(window, event);
}

} // anonymous namespace

SettingsButton::SettingsButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing
) : Button(topLeft, width, height, showing, State::Normal) 
{
    sprite_ = loadSpriteNormal();
    sprite_.setPosition(topLeft_);
    sprite_.scaleInPixels({width_, height_});
}

void SettingsButton::addButtonInShowList(Button* button)
{
    buttons_.addButton(button);
}

void SettingsButton::drawButtons(Graphics::Window& window) const
{
    buttons_.drawButtons(window);
}

void SettingsButton::onPress(Graphics::Window& window, const Graphics::Event& event) 
{
    return;
}

void SettingsButton::onRelease(Graphics::Window& window, const Graphics::Event& event) 
{
    if (state_ == State::Released)
    {
        state_  = State::Normal;
        sprite_ = loadSpriteHover();
    }
    else
    {
        state_  = State::Released;
        doReleaseAction(window, sprite_, buttons_, event);
    }

    SET_SPRITE_CONDITIONS_AND_DRAW();
}

void SettingsButton::onHover(Graphics::Window& window, const Graphics::Event& event) 
{
    if (state_ != State::Released)
        sprite_ = loadSpriteHover();
    else
        doReleaseAction(window, sprite_, buttons_, event);

    SET_SPRITE_CONDITIONS_AND_DRAW();
}

void SettingsButton::onUnhover(Graphics::Window& window, const Graphics::Event& event) 
{   
    switch (state_)
    {
        case State::Released:
            doReleaseAction(window, sprite_, buttons_, event);
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
        onUnhover(window, event);
        return;
    }

    switch (event.type)
    {
        case Graphics::Event::EventType::MouseButtonReleased:
            onRelease(window, event);
            break;
        
        default:
            onHover(window, event);
            break;
    }
}
} // namespace Gui