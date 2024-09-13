#include <cassert>

#include "Gui/ButtonManager.hpp"

namespace Gui
{

int ButtonManager::addButton(Button* button)
{
    buttons_.push_back(button);

    return buttons_.size() - 1;
}

void ButtonManager::deleteButton(Button* button)
{
    std::remove(buttons_.begin(), buttons_.end(), button);
}

void ButtonManager::manageButtons(Graphics::Window& window, const Graphics::Event& event)
{
    for (Button* button : buttons_)
    {
        assert(button);

        button->interact(window, event);

        if (button->showing())
            window.drawSprite(*button);
    }
}

} // namespace Gui