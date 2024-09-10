#include "Gui/Button.hpp"

#include "Graphics/Mouse.hpp"

#include <iostream>

namespace Gui
{

Button::Button(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state
) : topLeft_(topLeft), width_(width), height_(height), showing_(showing), state_(state) {}

bool Button::hovered(const Graphics::Window& window) const
{
    Graphics::WindowPoint mousePos = Graphics::Mouse::getPosition(window);

    if (topLeft_.x <= mousePos.x && mousePos.x <= topLeft_.x + width_ &&
        topLeft_.y <= mousePos.y && mousePos.y <= topLeft_.y + height_)
        return true;

    return false;
}

void Button::interact(Graphics::Window& window, const Graphics::Event& event)
{
    if (!hovered(window))
    {
        onUnhover(window);
        return;
    }

    switch (event.type)
    {
        case Graphics::Event::EventType::MouseButtonReleased:

            onRelease(window);
            break;
        
        case Graphics::Event::EventType::MouseButtonPressed:
            onPress(window);
            break;
        
        default:
            onHover(window);
            break;
    }    
}

Button::operator Graphics::Sprite() const
{ 
    return sprite_;
}

} // namespace Gui