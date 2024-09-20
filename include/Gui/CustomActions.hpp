#ifndef CUSTOM_ACTIONS_HPP
#define CUSTOM_ACTIONS_HPP

#include "Gui/Button.hpp"
#include "Gui/ButtonManager.hpp"
#include "Gui/SettingsButton.hpp"
#include "Scene/Transformable.hpp"
#include "Scene/Vector.hpp"
#include "Graphics/PixelsArray.hpp"


namespace Gui
{

class Action
{
public:
    virtual void operator()() = 0;

    virtual ~Action() = default;
};

class ActionWithButton : public Action
{
protected:
    Button* button_;

public:
    ActionWithButton(Button* button) : button_(button) {}

    virtual void operator()() override = 0;

    virtual ~ActionWithButton() override = default;
};

class EmptyAction : public Action
{
public:
    
    virtual void operator()() override { return; }

    virtual ~EmptyAction() override = default;
};

class MoveAction : public Action
{
    Scene::Transformable* object_;
    Scene::Vector moveDirection_;

public:
    MoveAction(Scene::Transformable* object, const Scene::Vector& moveDirection);

    virtual void operator()() override;
};

class ColorSphereAction : public ActionWithButton
{
    Scene::Sphere* sphere_;
    Graphics::Color color_;

public:
    ColorSphereAction(Button* button, Scene::Sphere* sphere, const Graphics::Color& color);

    virtual void operator()() override;
};

class ShowButtonsAction : public Action
{
    SettingsButton*        button_;
    Graphics::Window&      window_;
    const Graphics::Event& event_;

public:
    ShowButtonsAction(SettingsButton* button, Graphics::Window& window, const Graphics::Event& event);

    virtual void operator()() override;
};

class HideButtonsAction : public Action
{
    SettingsButton*   button_;
    Graphics::Window& window_;
    const Graphics::Event&  event_;

public:
    HideButtonsAction(SettingsButton* button, Graphics::Window& window, const Graphics::Event& event);

    virtual void operator()() override;
};

} // namespace Gui


#endif // CUSTOM_ACTIONS_HPP