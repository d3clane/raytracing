#include "Gui/ColorSphereButton.hpp"

namespace Gui
{

ColorSphereButton::ColorSphereButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state,
    const Graphics::Sprite& initNormalSprite, const Graphics::Sprite& initHoverSprite, 
    const Graphics::Sprite& initReleaseSprite, const Graphics::Sprite& initPressedSprite,
    Scene::Sphere* sphere, const Graphics::Color& color
) : Button(
    topLeft, width, height, showing, state, 
    initNormalSprite, initHoverSprite, initReleaseSprite, initPressedSprite
), sphere_(sphere), color_(color)
{
}

void ColorSphereButton::action(Graphics::Window& window, const Graphics::Event& event)
{
    sprite_ = releasedSprite_;
    sphere_->color(color_);
    state_  = State::Normal;
}

void ColorSphereButton::undoAction(Graphics::Window& window, const Graphics::Event& event)
{
    return;
}


} // namespace Gui