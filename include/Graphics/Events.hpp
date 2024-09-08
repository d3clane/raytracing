#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Graphics.hpp>
#include "Graphics/GraphicsWindow.hpp"

namespace Graphics
{

class Event
{
    sf::Event sfEvent;
    
public:
    enum class EventType
    {
        None,

        Closed,
        KeyPressed,
        MouseMove,
        MouseButtonPressed,
        MouseButtonReleased
    };

    enum class KeyCode
    {
        None, 

        W,
        S,
        A,
        D,
        
        Q,
        E,
    };

    EventType type;

    union
    {
        WindowPoint mousePos;
        Mouse::Button mouseButton;
        KeyCode keyCode;
    };


    Event();
    
    friend bool Window::pollEvent(Event& event);
};

} // Graphics

#endif // EVENTS_HPP