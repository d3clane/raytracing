#include "Gui/Button.hpp"

#include "Graphics/Mouse.hpp"

namespace Gui
{

namespace 
{

void configureSprite(
    Graphics::Sprite& sprite, 
    unsigned int width, unsigned int height, const Graphics::WindowPoint& topLeft
)
{
    sprite.setPosition(topLeft);
    sprite.scaleInPixels({width, height});
}

} // namespace anonymous
Button::Button(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state,
    const Graphics::Sprite& initNormalSprite, const Graphics::Sprite& initHoverSprite, 
    const Graphics::Sprite& initReleaseSprite, const Graphics::Sprite& initPressedSprite
) : topLeft_(topLeft), width_(width), height_(height), showing_(showing), state_(state),
    normalSprite_(initNormalSprite), hoveredSprite_(initHoverSprite), 
    releasedSprite_(initReleaseSprite), pressedSprite_(initPressedSprite) 
{
    switch (state_)
    {
        case State::Normal:
            sprite_ = normalSprite_;
            break;
        
        case State::Released:
            sprite_ = releasedSprite_;
            break;
        
        case State::Pressed:
            sprite_ = pressedSprite_;
            break;
        
        case State::Inactive:
            sprite_ = normalSprite_;
            break;
        
        default:
            break;
    }

    configureSprite(normalSprite_,   width_, height_, topLeft_);
    configureSprite(releasedSprite_, width_, height_, topLeft_);
    configureSprite(hoveredSprite_,    width_, height_, topLeft_);
    configureSprite(pressedSprite_,  width_, height_, topLeft_);

    sprite_ = normalSprite_;
}

bool Button::isHovered(const Graphics::Window& window) const
{
    Graphics::WindowPoint mousePos = Graphics::Mouse::getPosition(window);

    if (topLeft_.x <= mousePos.x && mousePos.x <= topLeft_.x + width_ &&
        topLeft_.y <= mousePos.y && mousePos.y <= topLeft_.y + height_)
        return true;

    return false;
}

void Button::interact(Graphics::Window& window, const Graphics::Event& event)
{
    if (!isHovered(window))
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

void Button::onPress(Graphics::Window& window, const Graphics::Event& event)
{
    return;
}

void Button::onRelease(Graphics::Window& window, const Graphics::Event& event)
{
    if (state_ == State::Released)
    {
        state_  = State::Normal;
        sprite_ = normalSprite_;
    }
    else
        action(window, event);
}

void Button::onHover  (Graphics::Window& window, const Graphics::Event& event)
{
    if (state_ != State::Released)
        sprite_ = hoveredSprite_;
    else
        action(window, event);
}

void Button::onUnhover(Graphics::Window& window, const Graphics::Event& event)
{
    switch (state_)
    {
        case State::Released:
            action(window, event);
            break;

        case State::Normal:
            sprite_ = normalSprite_;
            break;

        default: // unreachable
            assert(false);
            break;
    }
}

Button::operator Graphics::Sprite() const
{ 
    return sprite_;
}

} // namespace Gui