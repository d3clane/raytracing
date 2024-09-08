#include "Gui/Button.hpp"

namespace Gui
{

Button::Button(
    const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state
) : topLeft_(topLeft), width_(width), height_(height), showing_(showing), state_(state) {}

bool Button::hovered(const Graphics::Event& event) const
{
    if (event.type != Graphics::Event::EventType::MouseMove) return false;
    
    

}

void Button::interact()
{
    if (!showing_) return;


    switch (state_)
    {
        case State::Normal:
            
    }
}

} // namespace Gui