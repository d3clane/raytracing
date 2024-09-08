#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Events.hpp"
#include "Graphics/PixelsArray.hpp"

#include "Scene/LightSource.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Camera.hpp"

int main()
{
    Graphics::Window window{800, 600, "RayTracing"};
    Scene::Sphere sphere{Scene::Point{400, 300, 0}, 200, Graphics::Color(255, 0, 255, 0)};

    Scene::CoordsSystem coords{1u, Scene::Point{0, 0, 0}};

    Scene::LightSource lightSource1{Scene::Point{-100, 300, 0}, Graphics::Color(255, 255, 0, 255)};
    Scene::LightSource lightSource2{Scene::Point{800, 600, 300}, Graphics::Color(0, 255, 255, 255)};
    Scene::LightSource lightSource3{Scene::Point{800, 0, -200}, Graphics::Color(255, 255, 255, 255)};

    Scene::Camera camera{Scene::Point{400, 300, 500}};

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
        window.display();
    }
}