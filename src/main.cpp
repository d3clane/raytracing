#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Events.hpp"
#include "Graphics/PixelsArray.hpp"

#include "Scene/LightSource.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Camera.hpp"

#include "Gui/SettingsButton.hpp"

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

    Gui::SettingsButton settingsButton{
        Graphics::WindowPoint{screenWidth - buttonWidth, 0}, 
        buttonWidth, buttonHeight, true
    };

    Gui::SettingsButton tmpButton1{
        Graphics::WindowPoint{screenWidth - buttonWidth, buttonHeight}, 
        buttonWidth, buttonHeight, true
    };

    Gui::SettingsButton tmpButton2{
        Graphics::WindowPoint{screenWidth - buttonWidth, 2 * buttonHeight}, 
        buttonWidth, buttonHeight, true
    };

    settingsButton.addButtonInShowList(&tmpButton1);
    settingsButton.addButtonInShowList(&tmpButton2);

    Gui::ButtonsArray firstLayerButtons;
    firstLayerButtons.addButton(&settingsButton);

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
        firstLayerButtons.interactWithButtons(window, event);
        //window.drawSprite(tmpButton1);
        window.display();
    }
}