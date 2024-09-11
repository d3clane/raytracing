#include "Gui/MoveButton.hpp"

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
    BASIC_LOADER("media/textures/SettingsButtonNormal.png");
}

Graphics::Sprite& loadSpriteRelease()
{
    BASIC_LOADER("media/textures/SettingsButtonRelease.jpeg");
}

Graphics::Sprite& loadSpriteHover()
{
    BASIC_LOADER("media/textures/SettingsButtonHover.png");
}

#undef BASIC_LOADER

void doReleaseAction(
    Graphics::Window& window, Graphics::Sprite& spriteToChange, 
    Scene::Sphere* sphere, const Scene::Vector& moveDirection
)
{
    spriteToChange = loadSpriteRelease();

    if (sphere)
        sphere->moveCenter(moveDirection);
}

} // anonymous namespace

MoveButton::MoveButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
    const Scene::Vector& moveDirection, Scene::Sphere* sphere
) : Button(topLeft, width, height, showing, State::Normal), moveDirection_(moveDirection), sphere_(sphere)
{
    sprite_ = loadSpriteNormal();
    sprite_.setPosition(topLeft_);
    sprite_.scaleInPixels({width_, height_});
}

void MoveButton::onPress(Graphics::Window& window, const Graphics::Event& event) 
{
    return;
}

void MoveButton::onRelease(Graphics::Window& window, const Graphics::Event& event) 
{
    if (state_ == State::Released)
    {
        state_  = State::Normal;
        sprite_ = loadSpriteHover();
    }
    else
    {
        state_  = State::Released;
        doReleaseAction(window, sprite_, sphere_, moveDirection_);
    }

    SET_SPRITE_CONDITIONS_AND_DRAW();
}

void MoveButton::onHover(Graphics::Window& window, const Graphics::Event& event) 
{
    if (state_ != State::Released)
        sprite_ = loadSpriteHover();
    else
        doReleaseAction(window, sprite_, sphere_, moveDirection_);

    SET_SPRITE_CONDITIONS_AND_DRAW();
}

void MoveButton::onUnhover(Graphics::Window& window, const Graphics::Event& event) 
{   
    switch (state_)
    {
        case State::Released:
            doReleaseAction(window, sprite_, sphere_, moveDirection_);
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

void MoveButton::interact(Graphics::Window& window, const Graphics::Event& event)
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