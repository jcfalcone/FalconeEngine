#include "rect.h"

namespace FalconeEngine
{
    namespace Physics
    {
        Rect::Rect()
        {
        }

        Rect::Rect(float posCenterX, float posCenterY, float width, float height)
        {
            this->center = Vector2(posCenterX, posCenterY);
            this->size   = Vector2(width, height);

            this->updateSize();
        }

        Vector2 Rect::GetCenter() const
        {
            return this->center;
        }

        void Rect::setCenter(const float posX, const float posY)
        {
            this->center.x = posX;
            this->center.y = posY;

            this->updateSize();
        }

        void Rect::setCenter(const Vector2 pos)
        {
            this->center = pos;

            this->updateSize();
        }

        float Rect::getLeft() const
        {
            return this->min.x;
        }

        float Rect::getRight() const
        {
            return this->max.x;
        }

        float Rect::getTop() const
        {
            return this->max.y;
        }

        float Rect::getBottom() const
        {
            return this->min.y;
        }

        void Rect::updateSize()
        {
            this->min    = Vector2(this->center.x - (this->size.x * 0.5f), this->center.y - (this->size.y * 0.5f));
            this->max    = Vector2(this->center.x + (this->size.x * 0.5f), this->center.y + (this->size.y * 0.5f));
        }

        Vector2 Rect::getMin() const
        {
            return this->min;
        }

        Vector2 Rect::getMax() const
        {
            return this->max;
        }
    }
}
