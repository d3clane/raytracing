#ifndef BUTTON_MANAGER_HPP
#define BUTTON_MANAGER_HPP

#include <vector>

#include "Gui/Button.hpp"
#include "Other/TypeErasure.hpp"
#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Events.hpp"

namespace Gui
{

class ButtonManager
{
public:
    struct ButtonWithInfo
    {
        Button button;

        std::vector< TypeErasureFuncWithParams > funcsToCallNow;
    };

    int  addButton(const Button&  button, TypeErasureFuncWithParams funcToCallToInteractWithButton);
    void deleteButton(int buttonId);

    void manageButtons(Graphics::Window& window, const Graphics::Event& event);

    std::vector< ButtonWithInfo > buttons_; // for debug purpose ONLY
private:
    //std::vector< ButtonWithInfo > buttons_;
};

} // namespace Gui

#endif // BUTTON_MANAGER_HPP