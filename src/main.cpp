#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Events.hpp"
#include "Graphics/PixelsArray.hpp"

#include "Scene/LightSource.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Camera.hpp"

#include "Gui/Button.hpp"
#include "Gui/SettingsButton.hpp"
#include "Gui/CustomActions.hpp"

#include <iostream>

void func(Gui::Action* act) { (*act)(); }

#define TEXTURE_LOAD(FILE_NAME, TEXTURE_NAME, SPRITE_NAME)      \ 
    Graphics::Texture TEXTURE_NAME;                             \
    Graphics::Sprite  SPRITE_NAME;                              \
    TEXTURE_NAME.loadFromFile(FILE_NAME);                       \
    SPRITE_NAME.setTexture(TEXTURE_NAME);                   

int main()
{
    const size_t screenWidth  = 800;
    const size_t screenHeight = 600;
    const size_t buttonWidth  = 128;
    const size_t buttonHeight = 64;

    const Graphics::Color black{0, 0, 0, 255};
    const Graphics::Color white{255, 255, 255, 255};
    const Graphics::Color red  {255, 0, 0, 255};
    const Graphics::Color green{0, 255, 0, 255};
    const Graphics::Color blue {0, 0, 255, 255};
    const Graphics::Color yellow{255, 255, 0, 255};
    const Graphics::Color purple{255, 0, 255, 255};
    const Graphics::Color cyan {0, 255, 255, 255};

    Graphics::Window window{screenWidth, screenHeight, "RayTracing"};
    Scene::Sphere sphere{Scene::Point{screenWidth / 2, screenHeight / 2, 0}, screenHeight / 3, 
        purple
    };

    Scene::CoordsSystem coords{1u, Scene::Point{0, 0, 0}};

    Scene::LightSource lightSource1{Scene::Point{-100, screenHeight / 2, 0}, yellow};
    Scene::LightSource lightSource2{Scene::Point{screenWidth, screenHeight, 300}, cyan};

    Scene::LightSource lightSource3{Scene::Point{screenWidth, 0, -200}, white};

    Scene::Camera camera{Scene::Point{screenWidth / 2, screenHeight / 2, 500}};

    TEXTURE_LOAD("media/textures/buttonNormal.jpeg" , normalTexture , normalSprite  );
    TEXTURE_LOAD("media/textures/buttonReleased.png", releaseTexture, releasedSprite);
    TEXTURE_LOAD("media/textures/buttonHovered.png" , hoverTexture  , hoverSprite   );
    Graphics::Sprite pressedSprite{};

    TEXTURE_LOAD("media/textures/redButton.png"   , colorRedTexture  , colorRedSprite    );
    TEXTURE_LOAD("media/textures/greenButton.jpeg", colorGreenTexture, colorGreenSprite  );
    TEXTURE_LOAD("media/textures/blueButton.png"  , colorBlueTexture , colorBlueSprite   );
    TEXTURE_LOAD("media/textures/whiteButton.png" , colorWhiteTexture, colorWhiteSprite  );
    TEXTURE_LOAD("media/textures/purpleButton.png", colorPurpleTexture, colorPurpleSprite);

    std::chrono::milliseconds interactionDuration{2000};
    Graphics::Event event;

    Gui::SettingsButton settingsButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, 0}, 
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration
    };
    Gui::ShowButtonsAction showButtonsAction{&settingsButton, window, event};
    Gui::HideButtonsAction hideButtonsAction{&settingsButton, window, event};
    settingsButton.addAction    (&showButtonsAction);
    settingsButton.addUndoAction(&hideButtonsAction);

    const double moveStep = 2;
    Gui::HoverAnimatedButton moveRightButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - buttonHeight},
        buttonWidth, buttonHeight, true,
        normalSprite, hoverSprite, releasedSprite, pressedSprite,
        interactionDuration
    };

    Gui::MoveAction moveRightAction{&sphere, Scene::Vector{moveStep, 0, 0}};
    moveRightButton.addAction(&moveRightAction);

#if 0
    moveRight.addAction()
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
    Gui::ColorSphereButton colorRedButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 3 * buttonHeight},
        buttonWidth, buttonHeight, true, Gui::Button::State::Normal,
        colorRedSprite, colorRedSprite, colorRedSprite, colorRedSprite,
        &sphere, red
    };
    Gui::ColorSphereButton colorGreenButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 4 * buttonHeight},
        buttonWidth, buttonHeight, true, Gui::Button::State::Normal,
        colorGreenSprite, colorGreenSprite, colorGreenSprite, colorGreenSprite,
        &sphere, green
    };
    Gui::ColorSphereButton colorBlueButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 5 * buttonHeight},
        buttonWidth, buttonHeight, true, Gui::Button::State::Normal,
        colorBlueSprite, colorBlueSprite, colorBlueSprite, colorBlueSprite,
        &sphere, blue
    };
    Gui::ColorSphereButton colorWhiteButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 6 * buttonHeight},
        buttonWidth, buttonHeight, true, Gui::Button::State::Normal,
        colorWhiteSprite, colorWhiteSprite, colorWhiteSprite, colorWhiteSprite,
        &sphere, white
    };
    Gui::ColorSphereButton colorPurpleButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 7 * buttonHeight},
        buttonWidth, buttonHeight, true, Gui::Button::State::Normal,
        colorPurpleSprite, colorPurpleSprite, colorPurpleSprite, colorPurpleSprite,
        &sphere, purple
    };

    settingsButton.addButtonInShowList(&moveLeft            );
    settingsButton.addButtonInShowList(&moveRight           );
    settingsButton.addButtonInShowList(&moveUp              );
    settingsButton.addButtonInShowList(&moveDown            );
    settingsButton.addButtonInShowList(&moveForward         );
    settingsButton.addButtonInShowList(&moveBackwards       );
    settingsButton.addButtonInShowList(&colorRedButton      );
    settingsButton.addButtonInShowList(&colorGreenButton    );
    settingsButton.addButtonInShowList(&colorBlueButton     );
    settingsButton.addButtonInShowList(&colorWhiteButton    );
    settingsButton.addButtonInShowList(&colorPurpleButton   );
#endif

    settingsButton.addButtonInShowList(&moveRightButton);

    Gui::ButtonManager buttonsManager;
    buttonsManager.addButton(&settingsButton);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Graphics::Event::EventType::Closed)
                window.close();
        }

        if (event.type == Graphics::Event::EventType::MouseButtonReleased)
        {
            std::cout << "MY\n";
        }
        window.clear();
        
        Graphics::PixelsArray pixelsArray{window.width_, window.height_, Graphics::WindowPoint{0, 0}};

        lightSource1.highlightSphere(coords, sphere, camera, pixelsArray);
        lightSource2.highlightSphere(coords, sphere, camera, pixelsArray);
        lightSource3.highlightSphere(coords, sphere, camera, pixelsArray);

        camera.drawPixels(window, coords, pixelsArray);

        buttonsManager.manageButtons(window, event);
        window.display();
    }

}