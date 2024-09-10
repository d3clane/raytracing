#ifndef SETTINGS_BUTTON_HPP
#define SETTINGS_BUTTON_HPP

#include "Button.hpp"

namespace Gui
{

class SettingsButton : public Button
{  
public:
    SettingsButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing
    );

    virtual void onPress    (Graphics::Window& window);
    virtual void onRelease  (Graphics::Window& window);
    virtual void onHover    (Graphics::Window& window);
    virtual void onUnhover  (Graphics::Window& window);

    virtual void interact   (Graphics::Window& window, const Graphics::Event& event);
};

} // namespace Gui

#endif // SETTINGS_BUTTON_HPP