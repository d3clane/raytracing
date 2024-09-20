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

size_t SettingsButton::showListSize()
{
    return buttonManager_.size();
}

const ButtonManager& SettingsButton::buttonManager()
{
    return buttonManager_;
}

Button*& SettingsButton::operator[](int pos)
{
    return buttonManager_[pos];
}

const Button* SettingsButton::operator[](int pos) const
{
    return buttonManager_[pos];
}

} // namespace Gui