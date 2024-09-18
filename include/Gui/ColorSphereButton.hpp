#ifndef COLOR_SPHERE_BUTTON_HPP
#define COLOR_SPHERE_BUTTON_HPP

#include "Gui/Button.hpp"
#include "Scene/Sphere.hpp"

namespace Gui
{

class ColorSphereButton : public Button
{
    Scene::Sphere* sphere_;
    Graphics::Color color_;
public:
    ColorSphereButton(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state,
        const Graphics::Sprite& initNormalSprite, const Graphics::Sprite& initHoverSprite, 
        const Graphics::Sprite& initReleaseSprite, const Graphics::Sprite& initPressedSprite,
        Scene::Sphere* sphere, const Graphics::Color& color
    );

    virtual void action    (Graphics::Window& window, const Graphics::Event& event) override;
    virtual void undoAction(Graphics::Window& window, const Graphics::Event& event) override;
};

} // namespace Gui

#endif // COLOR_SPHERE_BUTTON_HPP