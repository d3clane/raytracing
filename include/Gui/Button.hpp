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

    bool hovered(const Graphics::Window& window) const;

    bool showing() const                   { return showing_; }
    void showing(bool newShowingCondition) { showing_ = newShowingCondition; }

    State state() const        { return state_; }
    void state(State newState) { state_ = newState; }

    virtual void interact (Graphics::Window& window, const Graphics::Event& event);

    virtual void onPress  (Graphics::Window& window, const Graphics::Event& event) = 0;
    virtual void onRelease(Graphics::Window& window, const Graphics::Event& event) = 0;
    virtual void onHover  (Graphics::Window& window, const Graphics::Event& event) = 0;
    virtual void onUnhover(Graphics::Window& window, const Graphics::Event& event) = 0;

    operator Graphics::Sprite() const;

protected:
    Graphics::WindowPoint topLeft_;
    unsigned int width_, height_;

    Graphics::Sprite sprite_;
    bool showing_;
    State state_;
};

class ButtonsArray
{
    std::vector< Button* > buttons_;
public:

    void addButton  (Button* button);
    void drawButtons(Graphics::Window& window) const;
    
    void interactWithButtons(Graphics::Window& window, const Graphics::Event& event);
};

} // namespace Gui

#endif