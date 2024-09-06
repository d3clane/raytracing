#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>

namespace Graphics
{

class Event;

struct Point
{
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

struct Line
{
    Point start, end;

    Line(const Point& start, const Point& end) : start(start), end(end) {}
};

class PixelsArray;

class Window
{
private:
    sf::RenderWindow window_;
    unsigned int width_, height_;

public:
    Window(int width, int height, const char* title);

    bool isOpen();
    void close();
    void clear();

    void drawLine  (Line line);
    void drawPixels(const PixelsArray& pixels);

    void display();

    unsigned int getWidth () const;
    unsigned int getHeight() const;

    bool pollEvent(Event& event);
};

} // Graphics

#endif // GRAPHICS_HPP