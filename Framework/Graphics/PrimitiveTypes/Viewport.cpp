#include "Viewport.h"

namespace Graphics
{
    Viewport::Viewport(int left, int top, int width, int height) : mLeft(left), mTop(top), mWidth(width), mHeight(height)
    {
    }

    Viewport::Viewport() : mLeft(0), mTop(0), mWidth(0), mHeight(0)
    {
    }

    Viewport::Viewport(Math::RectangleI rect)
        : mLeft(rect.position.x), mTop(rect.position.y), mWidth(rect.size.width), mHeight(rect.size.height)
    {
    }

    bool Viewport::operator==(const Viewport &other) const
    {
        return mLeft == other.mLeft && mTop == other.mTop && mWidth == other.mWidth && mHeight == other.mHeight;
    }

    bool Viewport::operator!=(const Viewport &other) const
    {
        return !(*this == other);
    }
}