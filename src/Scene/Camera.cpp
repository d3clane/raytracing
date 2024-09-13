#include "Scene/Camera.hpp"
#include "Scene/Vector.hpp"
#include "Graphics/PixelsArray.hpp"

namespace Scene
{

void Camera::drawPixels(Graphics::Window& window, const CoordsSystem& coordsSystem, 
                        const Graphics::PixelsArray& pixelsArray) const
{
    Graphics::WindowPoint windowCameraPos = coordsSystem.getPosInWindow(pos_);

    Graphics::PixelsArray pixelsArrayToDraw = pixelsArray;

    pixelsArrayToDraw.moveImage(
        pixelsArrayToDraw.middlePixelWindowPos() - windowCameraPos
    );

    window.drawPixels(pixelsArrayToDraw);
}


void Camera::move  (const Vector& delta) { pos_ = pos_ + delta; }
void Camera::setPos(const Point& pos   ) { pos_ = pos;          }

} // Scene