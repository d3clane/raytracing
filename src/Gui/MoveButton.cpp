#include "Gui/MoveButton.hpp"
#include "Graphics/Texture.hpp"

namespace Gui
{

MoveButton::MoveButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
    const Graphics::Sprite& normalSprite  , const Graphics::Sprite& hoveredSprite, 
    const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite,
    std::chrono::milliseconds interactionDuration, 
    Scene::Transformable* object, const Scene::Vector& moveDirection
) : HoverAnimatedButton(
        topLeft, width, height, showing,
        normalSprite, hoveredSprite, releasedSprite, pressedSprite, interactionDuration
    ), moveDirection_(moveDirection), object_(object)
{
}

void MoveButton::action(Graphics::Window& window, const Graphics::Event& event)
{
    state_  = State::Released;
    sprite_ = releasedSprite_;

    if (object_) object_->move(moveDirection_);
}

void MoveButton::undoAction(Graphics::Window& window, const Graphics::Event& event)
{
    return;
}

} // namespace Gui