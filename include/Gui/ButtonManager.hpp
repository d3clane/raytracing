#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <vector>

#include "Gui/Button.hpp"

namespace Gui
{

class ButtonManager
{
    std::vector< Button* > buttons_;

public:
    int  addButton   (Button* button);
    void deleteButton(Button* button);

    void manageButtons(Graphics::Window& window, const Graphics::Event& event);

    int size() const { return buttons_.size(); }

    Button*&      operator[](int index)       { return buttons_[index]; }
    const Button* operator[](int index) const { return buttons_[index]; }
};

} // namespace Gui

#endif // BUTTON_MANAGER_HPP