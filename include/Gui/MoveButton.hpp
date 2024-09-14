#ifndef MOVE_BUTTON_HPP
#define MOVE_BUTTON_HPP

#include "Gui/HoverAnimatedButton.hpp"
#include "Scene/Transformable.hpp"
#include "Scene/Vector.hpp"

namespace Gui
{

class MoveButton : public HoverAnimatedButton
{
    Scene::Transformable* object_;
    Scene::Vector  moveDirection_;

public:
    MoveButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
        const Graphics::Sprite& normalSprite  , const Graphics::Sprite& hoveredSprite, 
        const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite,
        std::chrono::milliseconds interactionDuration, 
        Scene::Transformable* object, const Scene::Vector& moveDirection
    );

    void object(Scene::Transformable* object)  { object_ = object; }
    Scene::Transformable*       object()       { return object_;   }
    const Scene::Transformable* object() const { return object_;   }

private:
    virtual void action     (Graphics::Window& window, const Graphics::Event& event) override;
    virtual void undoAction (Graphics::Window& window, const Graphics::Event& event) override;
};

} // namespace Gui

#endif // MOVE_BUTTON_HPP