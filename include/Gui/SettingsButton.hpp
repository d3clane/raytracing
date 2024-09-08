#ifndef SETTINGS_BUTTON_HPP
#define SETTINGS_BUTTON_HPP

#include "Button.hpp"

namespace Gui
{

class SettingsButton : public Button
{  
public:
    SettingsButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state
    ) : Button(topLeft, width, height, showing, state) {};

    virtual void onPress    (Graphics::Window& window);
    virtual void onRelease  (Graphics::Window& window);
    virtual void onHover    (Graphics::Window& window);
    virtual void onUnhover  (Graphics::Window& window);
private:
    void tmp(const char* fileName);
};

} // namespace Gui

#endif // SETTINGS_BUTTON_HPP