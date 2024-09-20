#ifndef SETTINGS_BUTTON_HPP
#define SETTINGS_BUTTON_HPP

#include "Gui/HoverAnimatedButton.hpp"
#include "Gui/ButtonManager.hpp"

namespace Gui
{

class SettingsButton : public HoverAnimatedButton
{
    ButtonManager buttonManager_;
    
public:
    SettingsButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
        const Graphics::Sprite& normalSprite  , const Graphics::Sprite& hoveredSprite, 
        const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite,
        std::chrono::milliseconds interactionDuration
    );

    void addButtonInShowList     (Button* button);
    void deleteButtonFromShowList(Button* button);
    size_t showListSize();

    const ButtonManager& buttonManager();

    Button*&      operator[](int pos);
    const Button* operator[](int pos) const;
};

} // namespace Gui

#endif // SETTINGS_BUTTON_HPP