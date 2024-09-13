#include "Gui/ButtonManager.hpp"

namespace Gui
{

namespace 
{

void callButtonFuncs(ButtonManager::ButtonWithInfo& button)
{
    for (TypeErasureFuncWithParams& func : button.funcsToCallNow)
        func();
}


} // namespace anonymous

int ButtonManager::addButton(const Button& button, TypeErasureFuncWithParams funcToCallToInteractWithButton)
{
    buttons_.push_back(
        ButtonWithInfo{ button, std::vector{ funcToCallToInteractWithButton } }
    );

    return (int)buttons_.size() - 1;
}

void ButtonManager::deleteButton(int buttonId)
{
    buttons_.erase(buttons_.begin() + buttonId);
}

void ButtonManager::manageButtons(Graphics::Window& window, const Graphics::Event& event)
{
    for (ButtonWithInfo& button : buttons_)
    {
        callButtonFuncs(button);

        if (button.button.showing())
            window.drawSprite(button.button);
    }
}

} // namespace Gui