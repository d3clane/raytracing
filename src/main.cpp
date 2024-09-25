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

    const Graphics::Color black {0, 0, 0, 255};
    const Graphics::Color white {255, 255, 255, 255};
    const Graphics::Color red   {255, 0, 0, 255};
    const Graphics::Color green {0, 255, 0, 255};
    const Graphics::Color blue  {0, 0, 255, 255};
    const Graphics::Color yellow{255, 255, 0, 255};
    const Graphics::Color purple{255, 0, 255, 255};
    const Graphics::Color cyan  {0, 255, 255, 255};

    Graphics::Window window{screenWidth, screenHeight, "RayTracing"};
    Scene::Sphere sphere{Scene::Point{screenWidth / 2, screenHeight / 2, 0}, screenHeight / 3, purple};

    Scene::CoordsSystem coords{1u, Scene::Point{0, 0, 0}};

    Scene::LightSource lightSource1{Scene::Point{-100, screenHeight / 2, 0}, yellow};
    Scene::LightSource lightSource2{Scene::Point{screenWidth, screenHeight, 300}, cyan};
    Scene::LightSource lightSource3{Scene::Point{screenWidth, 0, -200}, white};

    Scene::Camera camera{Scene::Point{screenWidth / 2, screenHeight / 2, 500}};

    TEXTURE_LOAD("media/textures/buttonNormal.jpeg" , normalTexture , normalSprite  );
    TEXTURE_LOAD("media/textures/buttonReleased.png", releaseTexture, releasedSprite);
    TEXTURE_LOAD("media/textures/buttonHovered.png" , hoverTexture  , hoveredSprite   );
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
        normalSprite, hoveredSprite, releasedSprite, pressedSprite,
        interactionDuration
    };
    Gui::ShowButtonsAction showButtonsAction{&settingsButton, window, event};
    Gui::HideButtonsAction hideButtonsAction{&settingsButton, window, event};
    settingsButton.addAction    (&showButtonsAction);
    settingsButton.addUndoAction(&hideButtonsAction);

    const double moveStep = 2;

    Gui::MoveAction moveRightAction         {&sphere, Scene::Vector{moveStep, 0, 0 }};
    Gui::MoveAction moveLeftAction          {&sphere, Scene::Vector{-moveStep, 0, 0}};
    Gui::MoveAction moveUpAction            {&sphere, Scene::Vector{0, -moveStep, 0}};
    Gui::MoveAction moveDownAction          {&sphere, Scene::Vector{0, moveStep, 0 }};
    Gui::MoveAction moveForwardAction       {&sphere, Scene::Vector{0, 0, -moveStep}};
    Gui::MoveAction moveBackwardsAction     {&sphere, Scene::Vector{0, 0, moveStep }};

    Gui::HoverAnimatedButton::CtorParams staticAnimatedButtonParams{
        interactionDuration, 
        Gui::Button::CtorParams(
            Graphics::WindowPoint{0, 0}, buttonWidth, buttonHeight, true, 
            Gui::Button::State::Normal, normalSprite, hoveredSprite, releasedSprite, pressedSprite
        )
    };

    Gui::HoverAnimatedButton moveRightButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - buttonHeight}, staticAnimatedButtonParams
    };
    moveRightButton.addAction(&moveRightAction);

    
    Gui::HoverAnimatedButton moveDownButton{
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - buttonHeight}, staticAnimatedButtonParams
    };
    moveDownButton.addAction(&moveDownAction);

    Gui::HoverAnimatedButton moveLeftButton{
        Graphics::WindowPoint{screenWidth - 3 * buttonWidth, screenHeight - buttonHeight}, staticAnimatedButtonParams
    };
    moveLeftButton.addAction(&moveLeftAction);

    Gui::HoverAnimatedButton moveUpButton{
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - 2 * buttonHeight}, staticAnimatedButtonParams
    };
    moveUpButton.addAction(&moveUpAction);

    Gui::HoverAnimatedButton moveForwardButton{
        Graphics::WindowPoint{0, screenHeight - 2 * buttonHeight}, staticAnimatedButtonParams
    };
    moveForwardButton.addAction(&moveForwardAction);
    
    Gui::HoverAnimatedButton moveBackwardsButton{
        Graphics::WindowPoint{0, screenHeight - buttonHeight}, staticAnimatedButtonParams
    };
    moveBackwardsButton.addAction(&moveBackwardsAction);

    Gui::Button::CtorParams staticColorButtonParams{
        Graphics::WindowPoint{0, 0}, buttonWidth, buttonHeight, true, 
        Gui::Button::State::Normal, colorRedSprite, colorRedSprite, colorRedSprite, colorRedSprite
    };


    Gui::Button colorRedButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 3 * buttonHeight}, colorRedSprite,
        staticColorButtonParams
    };
    Gui::Button colorGreenButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 4 * buttonHeight}, colorGreenSprite,
        staticColorButtonParams
    };
    Gui::Button colorBlueButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 5 * buttonHeight}, colorBlueSprite,
        staticColorButtonParams
    };
    Gui::Button colorWhiteButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 6 * buttonHeight}, colorWhiteSprite,
        staticColorButtonParams
    };
    Gui::Button colorPurpleButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 7 * buttonHeight}, colorPurpleSprite,
        staticColorButtonParams
    };

    Gui::ColorSphereAction colorRedAction   {&colorRedButton, &sphere, red};
    Gui::ColorSphereAction colorGreenAction {&colorGreenButton, &sphere, green};
    Gui::ColorSphereAction colorBlueAction  {&colorBlueButton, &sphere, blue};
    Gui::ColorSphereAction colorWhiteAction {&colorWhiteButton, &sphere, white};
    Gui::ColorSphereAction colorPurpleAction{&colorPurpleButton, &sphere, purple};

    colorRedButton.addAction    (&colorRedAction);
    colorGreenButton.addAction  (&colorGreenAction);
    colorBlueButton.addAction   (&colorBlueAction);
    colorWhiteButton.addAction  (&colorWhiteAction);
    colorPurpleButton.addAction (&colorPurpleAction);

    settingsButton.addButtonInShowList(&moveLeftButton      );
    settingsButton.addButtonInShowList(&moveRightButton     );
    settingsButton.addButtonInShowList(&moveUpButton        );
    settingsButton.addButtonInShowList(&moveDownButton      );
    settingsButton.addButtonInShowList(&moveForwardButton   );
    settingsButton.addButtonInShowList(&moveBackwardsButton );
    settingsButton.addButtonInShowList(&colorRedButton      );
    settingsButton.addButtonInShowList(&colorGreenButton    );
    settingsButton.addButtonInShowList(&colorBlueButton     );
    settingsButton.addButtonInShowList(&colorWhiteButton    );
    settingsButton.addButtonInShowList(&colorPurpleButton   );

    Gui::ButtonManager buttonsManager;
    buttonsManager.addButton(&settingsButton);

    while (window.isOpen())
    {
        event = {};
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

        buttonsManager.manageButtons(window, event);
        window.display();
    }

}
