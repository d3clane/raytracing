#include "Graphics/PixelsArray.hpp"
#include "Gui/HoverAnimatedButton.hpp"

#include <iostream>

namespace Gui
{

namespace 
{

void setColorAlpha(Graphics::Sprite& sprite, const uint8_t alpha)
{
    Graphics::Color color = sprite.getColor();
    sprite.setColor({color.red_, color.green_, color.blue_, alpha});
}

void animate(
    Graphics::Window& window, Graphics::Sprite& sprite_, Graphics::Sprite& prevSprite_,
    const std::chrono::steady_clock::time_point& timeBegin, const std::chrono::milliseconds& duration
)
{
    Graphics::Color color = sprite_.getColor();

    using ms = std::chrono::milliseconds;
    auto timeNow = std::chrono::steady_clock::now();

    color.alpha_ += std::min(
        255 * (double)std::chrono::duration_cast<ms>(timeNow - timeBegin).count() / duration.count(),
        255. - color.alpha_
    );

    sprite_.setColor(color);

    setColorAlpha(prevSprite_, 255 - color.alpha_);

    window.drawSprite(prevSprite_);

    std::cout << "sprite: " << (int)sprite_.getColor().alpha_ << "prev: " << (int)prevSprite_.getColor().alpha_ << std::endl;
}

} // namespace anonymous

void HoverAnimatedButton::PrevSpriteWrap::setPrevSprite(const Graphics::Sprite& sprite)
{
    prevSprite_ = sprite;
    setColorAlpha(prevSprite_, 0);
}

Graphics::Sprite& HoverAnimatedButton::PrevSpriteWrap::getPrevSpriteLink()
{
    return prevSprite_;
}
        
HoverAnimatedButton::PrevSpriteWrap::operator Graphics::Sprite&()
{
    return prevSprite_;
}

HoverAnimatedButton::HoverAnimatedButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
    const Graphics::Sprite& normalSprite, const Graphics::Sprite& releasedSprite, 
    const Graphics::Sprite& hoverSprite, const Graphics::Sprite& pressedSprite,
    std::chrono::milliseconds interactionDuration
) : Button(
        topLeft, width, height, showing, State::Normal,
        normalSprite, hoverSprite, releasedSprite, pressedSprite
    ), interactionDuration_(interactionDuration)
{
    prevSprite_.setPrevSprite(hoveredSprite_);
    sprite_     = normalSprite_;
    animationType_ = AnimationType::Unhovering;
}

void HoverAnimatedButton::onHover(Graphics::Window& window, const Graphics::Event& event)
{
    if (state_ == State::Released)
    {
        action(window, event);
        return;
    }

    if (animationType_ != AnimationType::Hovering)
    {
        interactionTimeBegin_ = std::chrono::steady_clock::now();
        animationType_ = AnimationType::Hovering;

        std::swap(sprite_, (Graphics::Sprite&)prevSprite_);
    }
    
    animate(window, sprite_, (Graphics::Sprite&)prevSprite_, interactionTimeBegin_, interactionDuration_);
}

void HoverAnimatedButton::onUnhover(Graphics::Window& window, const Graphics::Event& event)
{
    if (state_ == State::Released)
    {
        action(window, event);
        return;
    }

    if (animationType_ != AnimationType::Unhovering)
    {
        interactionTimeBegin_ = std::chrono::steady_clock::now();
        animationType_ = AnimationType::Unhovering;
        
        std::swap(sprite_, (Graphics::Sprite&)prevSprite_);

        //std::cout << (int)prevSprite_.getPrevSpriteLink().getColor().alpha_ << "\n";
    }

    animate(window, sprite_, (Graphics::Sprite&)prevSprite_, interactionTimeBegin_, interactionDuration_);
}

void HoverAnimatedButton::onRelease(Graphics::Window& window, const Graphics::Event& event)
{
    if (state_ == State::Released)
    {
        undoAction(window, event);

        state_  = State::Normal;
        sprite_ = hoveredSprite_;
        prevSprite_.setPrevSprite(normalSprite_);
        animationType_ = AnimationType::Hovering;
    }
    else
        action(window, event);
}

void HoverAnimatedButton::onPress(Graphics::Window& window, const Graphics::Event& event)
{
    return;
}

} // namespace Gui