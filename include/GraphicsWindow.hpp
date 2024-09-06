#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>

namespace Graphics
{

class Event;

struct WindowPoint
{
    int x, y;

    WindowPoint(int x, int y) : x(x), y(y) {}
};

struct WindowLine
{
    WindowPoint start, end;

    WindowLine(const WindowPoint& start, const WindowPoint& end) : start(start), end(end) {}
};

class PixelsArray;

class Window
{
private:
    sf::RenderWindow window_;

public:
    const unsigned int width_, height_;

    Window(int width, int height, const char* title);

    bool isOpen();
    void close();
    void clear();

    void drawLine  (WindowLine line);
    void drawPixels(const PixelsArray& pixels);

    void display();

    unsigned int getWidth () const;
    unsigned int getHeight() const;

    bool pollEvent(Event& event);
};

} // Graphics

#endif // GRAPHICS_HPP