#include "Gui/MoveButton.hpp"
#include "Graphics/Texture.hpp"

namespace Gui
{

MoveButton::MoveButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
    const Scene::Vector& moveDirection, Scene::Transformable* object,
    const Graphics::Sprite& normalSprite, const Graphics::Sprite& hoverSprite,
    const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite
) : Button(
        topLeft, width, height, showing, State::Normal,
        normalSprite, hoverSprite, releasedSprite, pressedSprite
    ), moveDirection_(moveDirection), object_(object)
{
}

void MoveButton::action(Graphics::Window& window, const Graphics::Event& event)
{
    state_  = State::Released;
    sprite_ = releasedSprite;

    if (object_) object_->move(moveDirection_);
}

} // namespace Gui