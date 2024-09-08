#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Sprite.hpp"
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
        Inactive,
    };

    Button(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state
    );

    virtual void onPress  () = 0;
    virtual void onRelease() = 0;
    virtual void onHover  () = 0;
    virtual void onUnhover() = 0;

    bool hovered(const Graphics::Event& event) const;
    void interact();

private:
    Graphics::WindowPoint topLeft_;
    unsigned int width_, height_;

    Graphics::Sprite sprite_;
    bool showing_;
    State state_;
};

} // namespace Gui

#endif