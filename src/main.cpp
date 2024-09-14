#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Events.hpp"
#include "Graphics/PixelsArray.hpp"

#include "Scene/LightSource.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Camera.hpp"

#include "Gui/SettingsButton.hpp"
#include "Gui/MoveButton.hpp"

#define TEXTURE_LOAD(FILE_NAME, TEXTURE_NAME, SPRITE_NAME)      \ 
    Graphics::Texture TEXTURE_NAME;                             \
    Graphics::Sprite  SPRITE_NAME;                              \
    TEXTURE_NAME.loadFromFile(FILE_NAME);                       \
    SPRITE_NAME.setTexture(TEXTURE_NAME);                   

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

    TEXTURE_LOAD("media/textures/SettingsButtonNormal.png",  normalTexture, normalSprite);
    TEXTURE_LOAD("media/textures/SettingsButtonRelease.jpeg", releaseTexture, releasedSprite);
    TEXTURE_LOAD("media/textures/SettingsButtonHover.png",   hoverTexture, hoverSprite);
    Graphics::Sprite pressedSprite{};

    std::chrono::milliseconds interactionDuration{20000};

    Gui::SettingsButton settingsButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, 0}, 
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration
    };

    const double moveStep = 2;
    Gui::MoveButton moveRight{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration, 
        &sphere, Scene::Vector{moveStep, 0, 0}
    };
    Gui::MoveButton moveDown{
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration, 
        &sphere, Scene::Vector{0, moveStep, 0}
    };
    Gui::MoveButton moveLeft{
        Graphics::WindowPoint{screenWidth - 3 * buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration, 
        &sphere, Scene::Vector{-moveStep, 0, 0}
    };
    Gui::MoveButton moveUp{
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - 2 * buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration, 
        &sphere, Scene::Vector{0, -moveStep, 0}
    };

    Gui::MoveButton moveForward{
        Graphics::WindowPoint{0, screenHeight - 2 * buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration, 
        &sphere, Scene::Vector{0, 0, -moveStep}
    };
    Gui::MoveButton moveBackwards{
        Graphics::WindowPoint{0, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration, 
        &sphere, Scene::Vector{0, 0, moveStep}
    };

    settingsButton.addButtonInShowList(&moveLeft);
    settingsButton.addButtonInShowList(&moveRight);
    settingsButton.addButtonInShowList(&moveUp);
    settingsButton.addButtonInShowList(&moveDown);
    settingsButton.addButtonInShowList(&moveForward);
    settingsButton.addButtonInShowList(&moveBackwards);

    Gui::ButtonManager buttonsManager;
    buttonsManager.addButton(&settingsButton);

    while (window.isOpen())
    {
        Graphics::Event event;
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
        buttonsManager.manageButtons(window, event);
        //window.drawSprite(tmpButton1);
        window.display();
    }
}