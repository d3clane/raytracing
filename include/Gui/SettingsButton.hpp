#ifndef SETTINGS_BUTTON_HPP
#define SETTINGS_BUTTON_HPP

#include "Gui/Button.hpp"
#include "Gui/ButtonManager.hpp"

namespace Gui
{

class SettingsButton : public Button
{
    ButtonManager buttonManager_;
    
public:
    SettingsButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing,
        const Graphics::Sprite& normalSprite, const Graphics::Sprite& hoverSprite,
        const Graphics::Sprite& releasedSprite, const Graphics::Sprite& pressedSprite
    );

    void addButtonInShowList     (Button* button);
    void deleteButtonFromShowList(Button* button);

private:
    virtual void onRelease(Graphics::Window& window, const Graphics::Event& event) override;
    virtual void action   (Graphics::Window& window, const Graphics::Event& event) override;
};

} // namespace Gui

#endif // SETTINGS_BUTTON_HPP