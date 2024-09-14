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

private:
    virtual void action     (Graphics::Window& window, const Graphics::Event& event) override;
    virtual void undoAction (Graphics::Window& window, const Graphics::Event& event) override;
};

} // namespace Gui

#endif // SETTINGS_BUTTON_HPP