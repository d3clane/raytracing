#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Events.hpp"

namespace Gui
{

class Action;

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
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state,
        const Graphics::Sprite& initNormalSprite, const Graphics::Sprite& initHoverSprite, 
        const Graphics::Sprite& initReleaseSprite, const Graphics::Sprite& initPressedSprite
    );

    virtual ~Button() = default;

    // functions
    bool isHovered(const Graphics::Window& window) const;
    bool isHovered(int mousePosX, int mousePosY)   const;
    
    bool showing() const                   { return showing_; }
    void showing(bool newShowingCondition) { showing_ = newShowingCondition; }

    State state() const        { return state_; }
    void state(State newState) { state_ = newState; }

    int  addAction       (Action* action);
    int  addUndoAction   (Action* action);
    void deleteAction    (Action* action);
    void deleteUndoAction(Action* action);
    void deleteAction    (int pos);
    void deleteUndoAction(int pos);

    

    virtual void interact   (Graphics::Window& window, const Graphics::Event& event);

    operator Graphics::Sprite() const;

private:
    virtual void onPress    (Graphics::Window& window, const Graphics::Event& event);
    virtual void onRelease  (Graphics::Window& window, const Graphics::Event& event);
    virtual void onHover    (Graphics::Window& window, const Graphics::Event& event);
    virtual void onUnhover  (Graphics::Window& window, const Graphics::Event& event);

protected:
    Graphics::WindowPoint topLeft_;
    unsigned int width_, height_;

    Graphics::Sprite sprite_;
    bool showing_;
    State state_;

    Graphics::Sprite normalSprite_;
    Graphics::Sprite hoveredSprite_;
    Graphics::Sprite releasedSprite_;
    Graphics::Sprite pressedSprite_;

    std::vector< Action* > actions_;
    std::vector< Action* > undoActions_;
};

void completeActions(const std::vector< Action* >& actions);

} // namespace Gui

#endif