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

class CreateHoverAnimatedButton
{
    size_t buttonWidth_;
    size_t buttonHeight_;

    bool showing_;

    Graphics::Sprite normalSprite_;
    Graphics::Sprite hoveredSprite_;
    Graphics::Sprite releasedSprite_;
    Graphics::Sprite pressedSprite_;

    std::chrono::milliseconds interactionDuration_;

public:
    CreateHoverAnimatedButton(
        size_t buttonWidth, size_t buttonHeight, bool showing,
        Graphics::Sprite normalSprite, Graphics::Sprite hoveredSprite,
        Graphics::Sprite releasedSprite, Graphics::Sprite pressedSprite,
        std::chrono::milliseconds interactionDuration
    ) : buttonWidth_(buttonWidth), buttonHeight_(buttonHeight), showing_(showing), 
        normalSprite_(normalSprite), hoveredSprite_(hoveredSprite), releasedSprite_(releasedSprite),
        pressedSprite_(pressedSprite), interactionDuration_(interactionDuration) {}

    Gui::HoverAnimatedButton operator()(
        const Graphics::WindowPoint& topLeftPos, Gui::Action* action
    );
};

class CreateColorButton
{
    size_t buttonWidth_;
    size_t buttonHeight_;

    bool showing_;

    Gui::Button::State state_;

public:
    CreateColorButton(
        size_t buttonWidth, size_t buttonHeight, bool showing, Gui::Button::State state
    ) : buttonWidth_(buttonWidth), buttonHeight_(buttonHeight), showing_(showing), state_(state) {}

    Gui::Button operator()(
        const Graphics::WindowPoint& topLeftPos, const Graphics::Sprite& sprite
    );
};

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

    CreateHoverAnimatedButton createHoverButton{
        buttonWidth, buttonHeight, true, 
        normalSprite, hoveredSprite, releasedSprite, pressedSprite,
        interactionDuration
    };

    auto moveRightButton = createHoverButton(
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - buttonHeight}, &moveRightAction
    );
    auto moveDownButton = createHoverButton(
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - buttonHeight}, &moveDownAction
    );
    auto moveLeftButton = createHoverButton(
        Graphics::WindowPoint{screenWidth - 3 * buttonWidth, screenHeight - buttonHeight}, &moveLeftAction
    );
    auto moveUpButton   = createHoverButton(
        Graphics::WindowPoint{screenWidth - 2 * buttonWidth, screenHeight - 2 * buttonHeight}, &moveUpAction
    );
    auto moveForwardButton = createHoverButton(
        Graphics::WindowPoint{0, screenHeight - 2 * buttonHeight}, &moveForwardAction
    );
    auto moveBackwardsButton = createHoverButton(
        Graphics::WindowPoint{0, screenHeight - buttonHeight}, &moveBackwardsAction
    );

    CreateColorButton createColorButton(buttonWidth, buttonHeight, true, Gui::Button::State::Normal);

    auto colorRedButton = createColorButton(
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 3 * buttonHeight}, colorRedSprite
    );
    auto colorGreenButton = createColorButton(
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 4 * buttonHeight}, colorGreenSprite
    );
    auto colorBlueButton = createColorButton(
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 5 * buttonHeight}, colorBlueSprite
    );
    auto colorWhiteButton = createColorButton(
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 6 * buttonHeight}, colorWhiteSprite
    );
    auto colorPurpleButton = createColorButton(
        Graphics::WindowPoint{screenWidth - buttonWidth, screenHeight - 7 * buttonHeight}, colorPurpleSprite
    );

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

Gui::HoverAnimatedButton CreateHoverAnimatedButton::operator()(
    const Graphics::WindowPoint& topLeftPos, Gui::Action* action
)
{
    Gui::HoverAnimatedButton button{
        topLeftPos,
        buttonWidth_, buttonHeight_, showing_,
        normalSprite_, hoveredSprite_, releasedSprite_, pressedSprite_,
        interactionDuration_
    };

    button.addAction(action);

    return button;
}

Gui::Button CreateColorButton::operator()(
    const Graphics::WindowPoint& topLeftPos, const Graphics::Sprite& sprite
)
{
    Gui::Button colorRedButton{
        topLeftPos, buttonWidth_, buttonHeight_, showing_, state_,
        sprite, sprite, sprite, sprite,
    };

    return colorRedButton;
}