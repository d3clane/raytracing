#ifndef MOVE_BUTTON_HPP
#define MOVE_BUTTON_HPP

#include "Gui/Button.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Vector.hpp"

namespace Gui
{

class MoveButton : public Button
{
    Scene::Sphere* sphere_;
    Scene::Vector  moveDirection_;

public:
    MoveButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
        const Scene::Vector& moveDirection, Scene::Sphere* sphere
    );

    void sphere(Scene::Sphere* sphere) { sphere_ = sphere; }

    Scene::Sphere*       sphere()       { return sphere_; }
    const Scene::Sphere* sphere() const { return sphere_; }

    virtual void interact   (Graphics::Window& window, const Graphics::Event& event);

    virtual void onPress    (Graphics::Window& window, const Graphics::Event& event);
    virtual void onRelease  (Graphics::Window& window, const Graphics::Event& event);
    virtual void onHover    (Graphics::Window& window, const Graphics::Event& event);
    virtual void onUnhover  (Graphics::Window& window, const Graphics::Event& event);
};

} // namespace Gui

#endif // MOVE_BUTTON_HPP