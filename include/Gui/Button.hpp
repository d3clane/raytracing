#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Graphics/GraphicsWindow.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Events.hpp"

#include "Other/TypeErasure.hpp"

namespace Gui
{

using MyTypeErasure::TypeErasureData;
using MyTypeErasure::TypeErasureFuncWithParams;

class Button
{ 
public:
    using ButtonFuncType   = void (*)(TypeErasureData params);

    enum class State
    {
        Normal,
        Released,
        Pressed,
        Inactive,
    };

    Button(
        const Graphics::WindowPoint& topLeft, unsigned int width, unsigned int height, bool showing, State state,
        ButtonFuncType interact, ButtonFuncType onPress, 
        ButtonFuncType onRelease, ButtonFuncType onHover, ButtonFuncType onUnhover,
        ButtonFuncType action,
        TypeErasureData buttonFuncsParams
    );

    // Public fields

    Graphics::Sprite spriteNormal;
    Graphics::Sprite spriteHovered;
    Graphics::Sprite spritePress;
    Graphics::Sprite spriteReleased;

    // Functions

    bool isHovered(const Graphics::Window& window) const;

    inline bool showing() const                   { return showing_; }
    inline void showing(bool newShowingCondition) { showing_ = newShowingCondition; }

    inline State state() const         { return state_; }
    inline void  state(State newState) { state_ = newState; }

    inline void interact (TypeErasureData params)     { interact_ (params);   }

    inline void onPress  (TypeErasureData params)     { onPress_  (params);   }
    inline void onRelease(TypeErasureData params)     { onRelease_(params);   }
    inline void onHover  (TypeErasureData params)     { onHover_  (params);   }
    inline void onUnhover(TypeErasureData params)     { onUnhover_(params);   }
    inline void action   (TypeErasureData params)     { action_   (params);   }

    inline void setInteract (ButtonFuncType newInteract )             { interact_     = newInteract;  }

    inline void setOnPress  (ButtonFuncType newOnPress  )             { onPress_      = newOnPress;   }
    inline void setOnRelease(ButtonFuncType newOnRelease)             { onRelease_    = newOnRelease; }
    inline void setOnHover  (ButtonFuncType newOnHover  )             { onHover_      = newOnHover;   }
    inline void setOnUnhover(ButtonFuncType newOnUnhover)             { onUnhover_    = newOnUnhover; }
    inline void setAction   (ButtonFuncType newAction   )             { action_       = newAction;    }

    inline       void  buttonFuncsParams(TypeErasureData data)        { buttonFuncsParams_ = data;    }
    inline       TypeErasureData buttonFuncsParams()                  { return buttonFuncsParams_;    } 
    inline const TypeErasureData buttonFuncsParams() const            { return buttonFuncsParams_;    }   

    inline Graphics::Sprite sprite() const                     { return spriteNow_;      }
    inline void             sprite(Graphics::Sprite newSprite) { spriteNow_ = newSprite; } 

    operator Graphics::Sprite() const;

private:
    Graphics::WindowPoint topLeft_;
    unsigned int width_, height_;

    Graphics::Sprite spriteNow_;

    bool showing_;
    State state_;

    ButtonFuncType interact_;

    ButtonFuncType onPress_;
    ButtonFuncType onRelease_;
    ButtonFuncType onHover_;
    ButtonFuncType onUnhover_;

    ButtonFuncType action_;

    TypeErasureData buttonFuncsParams_;
};

} // namespace Gui

#endif