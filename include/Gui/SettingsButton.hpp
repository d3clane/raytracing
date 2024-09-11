#ifndef SETTINGS_BUTTON_HPP
#define SETTINGS_BUTTON_HPP

#include "Button.hpp"

namespace Gui
{

class SettingsButton : public Button
{
    ButtonsArray buttons_;
    
public:
    SettingsButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing
    );

    void addButtonInShowList(Button* button);
    void drawButtons(Graphics::Window& window) const;

    virtual void onPress    (Graphics::Window& window, const Graphics::Event& event);
    virtual void onRelease  (Graphics::Window& window, const Graphics::Event& event);
    virtual void onHover    (Graphics::Window& window, const Graphics::Event& event);
    virtual void onUnhover  (Graphics::Window& window, const Graphics::Event& event);

    virtual void interact   (Graphics::Window& window, const Graphics::Event& event);
};

} // namespace Gui

#endif // SETTINGS_BUTTON_HPP