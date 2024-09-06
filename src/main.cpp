#include "GraphicsWindow.hpp"
#include "Sphere.hpp"
#include "Events.hpp"

int main()
{
    Graphics::Window window{800, 600, "RayTracing"};
    uint8_t tmp[4] = {0, 0, 0, 0};
    Scene::Sphere sphere{Scene::Point{400, 300, 0}, 200, tmp};

    Scene::CoordsSystem coords{Scene::Direction{1, 1, 1}, Scene::Point{0, 0, 0}};

    while (window.isOpen())
    {
        Graphics::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Graphics::Event::EventType::Closed)
                window.close();
        }

        window.clear();
        coords.drawSphere(window, sphere);
        window.display();
    }
}