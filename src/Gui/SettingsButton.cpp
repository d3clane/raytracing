#include "Gui/SettingsButton.hpp"

#include "Graphics/Texture.hpp"

#include <iostream>

namespace Gui
{

SettingsButton::SettingsButton(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
    const Graphics::Sprite& normalSprite  , const Graphics::Sprite& hoveredSprite, 
    const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite,
    std::chrono::milliseconds interactionDuration
) : HoverAnimatedButton(
        topLeft, width, height, showing,
        normalSprite, hoveredSprite, releasedSprite, pressedSprite, interactionDuration
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

void SettingsButton::action(Graphics::Window& window, const Graphics::Event& event)
{
    state_  = State::Released;
    sprite_ = releasedSprite_;

    for (int i = 0; i < buttonManager_.size(); ++i)
        buttonManager_[i]->showing(true);

    buttonManager_.manageButtons(window, event);
}

void SettingsButton::undoAction(Graphics::Window& window, const Graphics::Event& event)
{
    state_  = Button::State::Normal;
    sprite_ = normalSprite_;

    for (int i = 0; i < buttonManager_.size(); ++i)
        buttonManager_[i]->showing(false);
}

} // namespace Gui