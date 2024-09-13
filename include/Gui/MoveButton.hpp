#ifndef MOVE_BUTTON_HPP
#define MOVE_BUTTON_HPP

#include "Gui/Button.hpp"
#include "Scene/Transformable.hpp"
#include "Scene/Vector.hpp"

namespace Gui
{

class MoveButton : public Button
{
    Scene::Transformable* object_;
    Scene::Vector  moveDirection_;

public:
    MoveButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
        const Scene::Vector& moveDirection, Scene::Transformable* object,
        const Graphics::Sprite& normalSprite, const Graphics::Sprite& hoverSprite,
        const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite
    );

    void object(Scene::Transformable* object)  { object_ = object; }
    Scene::Transformable*       object()       { return object_;   }
    const Scene::Transformable* object() const { return object_;   }

private:
    virtual void action(Graphics::Window& window, const Graphics::Event& event) override;
};

} // namespace Gui

#endif // MOVE_BUTTON_HPP