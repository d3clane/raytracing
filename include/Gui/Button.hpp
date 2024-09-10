#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Events.hpp"

namespace Gui
{

class Button
{
public: 
    enum class State
    {
        Normal,
        Released,
        Pressed,
        Inactive,
    };

    Button(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state
    );

    virtual void onPress  (Graphics::Window& window) = 0;
    virtual void onRelease(Graphics::Window& window) = 0;
    virtual void onHover  (Graphics::Window& window) = 0;
    virtual void onUnhover(Graphics::Window& window) = 0;
    
    virtual void interact (Graphics::Window& window, const Graphics::Event& event);

    bool hovered(const Graphics::Window& window) const;

    operator Graphics::Sprite() const;
protected:
    Graphics::WindowPoint topLeft_;
    unsigned int width_, height_;

    Graphics::Sprite  sprite_;
    Graphics::Texture texture_;
    bool showing_;
    State state_;
};

} // namespace Gui

#endif