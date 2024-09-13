#include "Gui/SettingsButton.hpp"

#include "Graphics/Texture.hpp"

#include <iostream>

namespace Gui
{

namespace 
{

void undoReleaseAction(
    Graphics::Window& window,  const Graphics::Event&  event,
    Graphics::Sprite& sprite_, const Graphics::Sprite& normalSprite,
    Button::State& state_, ButtonManager& buttonManager_
)
{
    state_  = Button::State::Normal;
    sprite_ = normalSprite;

    for (int i = 0; i < buttonManager_.size(); ++i)
        buttonManager_[i]->showing(false);
}

} // namespace anonymous

SettingsButton::SettingsButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
    const Graphics::Sprite& normalSprite, const Graphics::Sprite& hoverSprite,
    const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite
) : Button(
        topLeft, width, height, showing, State::Normal, 
        normalSprite, hoverSprite, releasedSprite, pressedSprite
    ) 
{
}

void SettingsButton::addButtonInShowList(Button* button)
{
    buttonManager_.addButton(button);
}

void SettingsButton::deleteButtonFromShowList(Button* button)
{
    buttonManager_.deleteButton(button);
}

void SettingsButton::onRelease(Graphics::Window& window, const Graphics::Event& event)
{
    if (state_ == State::Released)
        undoReleaseAction(window, event, sprite_, normalSprite, state_, buttonManager_);
    else
        action(window, event);
}

void SettingsButton::action(Graphics::Window& window, const Graphics::Event& event)
{
    state_  = State::Released;
    sprite_ = releasedSprite;

    for (int i = 0; i < buttonManager_.size(); ++i)
        buttonManager_[i]->showing(true);

    buttonManager_.manageButtons(window, event);
}

} // namespace Gui