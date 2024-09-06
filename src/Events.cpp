#include "Events.hpp"

namespace Graphics
{

Event::Event() : type(EventType::None), mousePos(0, 0), keyCode(KeyCode::None) {}

} // namespace Graphics