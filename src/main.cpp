#include "GraphicsWindow.hpp"
#include "Sphere.hpp"
#include "Events.hpp"
#include "LightSource.hpp"
#include "PixelsArray.hpp"
#include "Camera.hpp"

int main()
{
    Graphics::Window window{800, 600, "RayTracing"};
    Scene::Sphere sphere{Scene::Point{400, 300, 0}, 200, Graphics::Color(255, 0, 0, 0)};

    Scene::CoordsSystem coords{Scene::PixelVector{1, 1, 1}, Scene::Point{0, 0, 0}};

    Scene::LightSource lightSource1{Scene::Point{0, 0, -50}, Graphics::Color(255, 255, 255, 255)};
    Scene::LightSource lightSource2{Scene::Point{800, 300, 100}, Graphics::Color(255, 255, 255, 255)};
    Scene::LightSource lightSource3{Scene::Point{0, 600, 100}, Graphics::Color(255, 255, 255, 255)};

    Scene::Camera camera{Scene::Point{0, 0, 0}};

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

        lightSource1.highlightSphere(coords, sphere, pixelsArray);
        lightSource2.highlightSphere(coords, sphere, pixelsArray);
        lightSource3.highlightSphere(coords, sphere, pixelsArray);

        camera.drawPixels(window, coords, pixelsArray);
        window.display();
    }
}