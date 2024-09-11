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
        onUnhover(window, event);
        return;
    }

    switch (event.type)
    {
        case Graphics::Event::EventType::MouseButtonReleased:

            onRelease(window, event);
            break;
        
        case Graphics::Event::EventType::MouseButtonPressed:
            onPress(window, event);
            break;
        
        default:
            onHover(window, event);
            break;
    }    
}

Button::operator Graphics::Sprite() const
{ 
    return sprite_;
}

void ButtonsArray::addButton(Button* button)
{
    buttons_.push_back(button);
}

void ButtonsArray::drawButtons(Graphics::Window& window) const
{
    for (Button* button : buttons_)
    {
        if (button->showing())
            window.drawSprite(*button);
    }
}

void ButtonsArray::interactWithButtons(Graphics::Window& window, const Graphics::Event& event)
{
    for (Button* button : buttons_)
        button->interact(window, event);
}

} // namespace Gui