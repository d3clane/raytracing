#include "Gui/CustomActions.hpp"
#include "Scene/Sphere.hpp"

namespace Gui
{

MoveAction::MoveAction(
    Scene::Transformable* object, const Scene::Vector& moveDirection
) : object_(object), moveDirection_(moveDirection)
{
}

void MoveAction::operator()()
{
    if (object_)
        object_->move(moveDirection_);
}

ColorSphereAction::ColorSphereAction(
    Button* button, Scene::Sphere* sphere, const Graphics::Color& color
) : ActionWithButton(button), sphere_(sphere), color_(color)
{
}

void ColorSphereAction::operator()() 
{ 
    if (sphere_)
        sphere_->color(color_);

    button_->state(Button::State::Normal);
}

ShowButtonsAction::ShowButtonsAction(
    SettingsButton* button, Graphics::Window& window, const Graphics::Event& event
) : button_(button), window_(window), event_(event)
{
}

void ShowButtonsAction::operator()()
{
    for (int i = 0; i < button_->showListSize(); ++i)
        (*button_)[i]->showing(true);

    button_->buttonManager().manageButtons(window_, event_);
}

HideButtonsAction::HideButtonsAction(
    SettingsButton* button, Graphics::Window& window, const Graphics::Event& event
) : button_(button), window_(window), event_(event)
{
}

void HideButtonsAction::operator()() 
{
    for (int i = 0; i < button_->showListSize(); ++i)
    {
        (*button_)[i]->showing(false);
        (*button_)[i]->state  (Button::State::Inactive);
    }
}

} // namespace Gui