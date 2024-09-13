#include "Gui/Button.hpp"

#include "Other/TypeErasure.hpp"

#include "Graphics/Texture.hpp"

#include <iostream>

namespace Gui
{

using MyTypeErasure::TypeErasureData;

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

} // anonymous namespace

struct MyParams
{
    Graphics::Window& window;
    const Graphics::Event& event;
};

#define CONVERT_PARAMS(PARAMS, OUT_PARAMS_VAR_NAME)     \
do                                                      \
{                                                       \
    OUT_PARAMS_VAR_NAME = (MyParams*)(PARAMS.data);     \
} while(0)

void onPress(Button& button, TypeErasureData paramsNoType) 
{
    return;
}

void onRelease(Button& button, TypeErasureData paramsNoType) 
{
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);

    if (button.state() == Button::State::Released)
    {
        button.state(Button::State::Normal);
        button.sprite(loadSpriteHover());
    } 
    else
    {
        button.state(Button::State::Released);
        //doReleaseAction(window, sprite_, buttons_, event);
    }

    //SET_SPRITE_CONDITIONS_AND_DRAW();
}

void onHover(Button& button, TypeErasureData paramsNoType) 
{
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);

    if (button.state() != Button::State::Released)
        button.sprite(loadSpriteHover());
    else;
        //doReleaseAction(window, sprite_, buttons_, event);

    //SET_SPRITE_CONDITIONS_AND_DRAW();
}

void onUnhover(Button& button, TypeErasureData paramsNoType) 
{   
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);
    switch (button.state())
    {
        case Button::State::Released:
            //doReleaseAction(window, sprite_, buttons_, event);
            break;

        case Button::State::Normal:
            button.sprite(loadSpriteNormal());
            break;

        default: // unreachable
            assert(false);
            break;
    }

    //SET_SPRITE_CONDITIONS_AND_DRAW();
}

void interact(
    Button& button, Graphics::Window& window, const Graphics::Event& event, 
    TypeErasureData paramsNoType
)
{
    if (!button.isHovered(window))
    {
        button.onUnhover(button, paramsNoType);
        return;
    }

    switch (event.type)
    {
        case Graphics::Event::EventType::MouseButtonReleased:
            button.onRelease(button, paramsNoType);
            break;
        
        default:
            button.onHover(button, paramsNoType);
            break;
    }
}

} // namespace Gui