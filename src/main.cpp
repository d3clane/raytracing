#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Events.hpp"
#include "Graphics/PixelsArray.hpp"

#include "Scene/LightSource.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Camera.hpp"

#include "Gui/ButtonManager.hpp"
#include "Gui/MoveButton.hpp"

//#include "Src/Gui/ButtonManager.cpp"

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
    params->button.sprite().setPosition(topLeft_);                                                  \
    sprite_.scaleInPixels({width_, height_});                                                       \
    showing_ = true;                                                                                \
                                                                                                    \
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
    Gui::Button& button;
    Graphics::Window& window;
    const Graphics::Event& event;
};

#define CONVERT_PARAMS(PARAMS, OUT_PARAMS_VAR_NAME)     \
do                                                      \
{                                                       \
    OUT_PARAMS_VAR_NAME = (MyParams*)(PARAMS.data);     \
} while(0)

void onPress(TypeErasureData paramsNoType) 
{
    return;
}

void onRelease(TypeErasureData paramsNoType) 
{
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);

    if (params->button.state() == Button::State::Released)
    {
        params->button.state(Button::State::Normal);
        params->button.sprite(loadSpriteHover());
    } 
    else
    {
        params->button.state(Button::State::Released);
        //doReleaseAction(window, sprite_, buttons_, event);
    }

    //SET_SPRITE_CONDITIONS_AND_DRAW();
}

void onHover(TypeErasureData paramsNoType) 
{
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);

    if (params->button.state() != Button::State::Released)
        params->button.sprite(loadSpriteHover());
    else;
        //doReleaseAction(window, sprite_, buttons_, event);

    //SET_SPRITE_CONDITIONS_AND_DRAW();
}

void onUnhover(TypeErasureData paramsNoType) 
{   
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);
    switch (params->button.state())
    {
        case Button::State::Released:
            //doReleaseAction(window, sprite_, buttons_, event);
            break;

        case Button::State::Normal:
            params->button.sprite(loadSpriteNormal());
            break;

        default: // unreachable
            assert(false);
            break;
    }

    //SET_SPRITE_CONDITIONS_AND_DRAW();
}

void interact(TypeErasureData paramsNoType)
{
    MyParams* params;
    CONVERT_PARAMS(paramsNoType, params);
    if (!params->button.isHovered(params->window))
    {
        params->button.onUnhover(paramsNoType);
        return;
    }

    switch (params->event.type)
    {
        case Graphics::Event::EventType::MouseButtonReleased:
            params->button.onRelease(paramsNoType);
            break;
        
        default:
            params->button.onHover(paramsNoType);
            break;
    }
}

} // namespace Gui

int main()
{
    const size_t screenWidth  = 800;
    const size_t screenHeight = 600;
    const size_t buttonWidth  = 64;
    const size_t buttonHeight = 32;

    Graphics::Window window{screenWidth, screenHeight, "RayTracing"};
    Scene::Sphere sphere{Scene::Point{screenWidth / 2, screenHeight / 2, 0}, screenHeight / 3, 
        Graphics::Color(255, 0, 255, 0)
    };

    Scene::CoordsSystem coords{1u, Scene::Point{0, 0, 0}};

    Scene::LightSource lightSource1{Scene::Point{-100, screenHeight / 2, 0}, Graphics::Color(255, 255, 0, 255)};
    Scene::LightSource lightSource2{Scene::Point{screenWidth, screenHeight, 300}, 
        Graphics::Color(0, 255, 255, 255)
    };
    Scene::LightSource lightSource3{Scene::Point{screenWidth, 0, -200}, Graphics::Color(255, 255, 255, 255)};

    Scene::Camera camera{Scene::Point{screenWidth / 2, screenHeight / 2, 500}};

    Gui::ButtonManager buttonManager;

    Gui::Button settingsButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, 0}, 
        buttonWidth, buttonHeight, true, Gui::Button::State::Normal,
        Gui::interact, Gui::onPress, Gui::onRelease, Gui::onHover, Gui::onUnhover, nullptr,
        MyTypeErasure::TypeErasureData{nullptr, nullptr, nullptr, nullptr}
    };

    Graphics::Event event;
    Gui::MyParams params{settingsButton, window, event};

    int buttonId = buttonManager.addButton(settingsButton, {Gui::interact, MyTypeErasure::TypeErasureData{&params, nullptr, nullptr, nullptr}});

#if 0
    const double moveStep = 2;
    Gui::MoveButton moveRight{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true, Scene::Vector{moveStep, 0, 0}, &sphere
    };
    Gui::MoveButton moveDown{
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true, Scene::Vector{0, moveStep, 0}, &sphere
    };
    Gui::MoveButton moveLeft{
        Graphics::WindowPoint{screenWidth - 3 * buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true, Scene::Vector{-moveStep, 0.01, 0}, &sphere
    };
    Gui::MoveButton moveUp{
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - 2 * buttonHeight},
        buttonWidth, buttonHeight, true, Scene::Vector{0, -moveStep, 0}, &sphere
    };

    Gui::MoveButton moveForward{ // move from the view camera
        Graphics::WindowPoint{0, screenHeight - 2 * buttonHeight},
        buttonWidth, buttonHeight, true, Scene::Vector{0, 0, -moveStep}, &sphere
    };
    Gui::MoveButton moveBackwards{ // move towards the view camera
        Graphics::WindowPoint{0, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true, Scene::Vector{0, 0, moveStep}, &sphere
    };

    settingsButton.addButtonInShowList(&moveLeft);
    settingsButton.addButtonInShowList(&moveRight);
    settingsButton.addButtonInShowList(&moveUp);
    settingsButton.addButtonInShowList(&moveDown);
    settingsButton.addButtonInShowList(&moveForward);
    settingsButton.addButtonInShowList(&moveBackwards);
#endif

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Graphics::Event::EventType::Closed)
                window.close();
        }

        window.clear();
        
        Graphics::PixelsArray pixelsArray{window.width_, window.height_, Graphics::WindowPoint{0, 0}};

        lightSource1.highlightSphere(coords, sphere, camera, pixelsArray);
        lightSource2.highlightSphere(coords, sphere, camera, pixelsArray);
        lightSource3.highlightSphere(coords, sphere, camera, pixelsArray);

        camera.drawPixels(window, coords, pixelsArray);

        //window.drawSprite(settingsButton);
        buttonManager.manageButtons(window, event);
        //firstLayerButtons.interactWithButtons(window, event);
        //window.drawSprite(tmpButton1);
        window.display();
    }
}