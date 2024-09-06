#include "Events.hpp"
#include "GraphicsWindow.hpp"
#include "PixelsArray.hpp"

namespace Graphics
{

namespace 
{

Event::KeyCode convertSfKeyCodeToKeyCode(sf::Keyboard::Key sfKeyCode);

Event::KeyCode convertSfKeyCodeToKeyCode(sf::Keyboard::Key sfKeyCode)
{
    switch (sfKeyCode)
    {
        case sf::Keyboard::Key::W:          return Event::KeyCode::W;
        case sf::Keyboard::Key::S:          return Event::KeyCode::S;
        case sf::Keyboard::Key::A:          return Event::KeyCode::A;
        case sf::Keyboard::Key::D:          return Event::KeyCode::D;
        case sf::Keyboard::Key::Q:          return Event::KeyCode::Q;
        case sf::Keyboard::Key::E:          return Event::KeyCode::E;
        default:                            return Event::KeyCode::None;
    }

    return Event::KeyCode::None;
}

} // Anonymous namespace

Window::Window(int width, int height, const char* title) : 
        window_(sf::VideoMode(width, height), title), height_(height), width_(width)
{
}

void Window::display()
{
    window_.display();
}

bool Window::isOpen()
{
    return window_.isOpen();
}

void Window::close()
{
    window_.close();
}

void Window::clear()
{
    window_.clear();
}

void Window::drawLine(WindowLine line)
{
    sf::Vertex drewLine[] =
    {
        sf::Vertex(sf::Vector2f(line.start.x, line.start.y)),
        sf::Vertex(sf::Vector2f(line.end.x,   line.end.y  )),
    };

    window_.draw(drewLine, sizeof(drewLine) / sizeof(*drewLine), sf::Lines);
}

void Window::drawPixels(const PixelsArray& pixels)
{
    sf::Texture texture;
    texture.create(pixels.width_, pixels.height_);
    sf::Sprite sprite;
    
    texture.update(pixels.pixels_);
    sprite.setTexture(texture);

    window_.draw(sprite);
}

unsigned int Window::getWidth () const
{
    return width_;
}

unsigned int Window::getHeight() const
{
    return height_;
}

bool Window::pollEvent(Event& event)
{
    bool result = window_.pollEvent(event.sfEvent);

    event.mousePos = WindowPoint(event.sfEvent.mouseMove.x, event.sfEvent.mouseMove.y);

    switch (event.sfEvent.type)
    {
        case sf::Event::Closed:
            event.type = Event::EventType::Closed;
            break;

        case sf::Event::KeyPressed:
            event.type = Event::EventType::KeyPressed;
            event.keyCode = convertSfKeyCodeToKeyCode(event.sfEvent.key.code);
            break;
        
        case sf::Event::MouseMoved:
            event.type = Event::EventType::MouseMove;
            event.mousePos = WindowPoint(event.sfEvent.mouseMove.x, event.sfEvent.mouseMove.y);
            break;
        
        default:
            event.type = Event::EventType::None;
            break;
    }

    return result;
}

} // Graphics