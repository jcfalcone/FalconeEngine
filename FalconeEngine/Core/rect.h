#ifndef RECT_H
#define RECT_H

#include "Vector2.h"

namespace FalconeEngine
{
    namespace Physics
    {
        class Rect
        {
        private:
            Vector2 center;
            Vector2 size;
            Vector2 min;
            Vector2 max;

            void updateSize();
        public:
            Rect();
            Rect(float posCenterX, float posCenterY, float width, float height);

            Vector2 GetCenter() const;
            void setCenter(const float posX, const float posY);
            void setCenter(const Vector2 pos);

            float getLeft() const;
            float getRight() const;

            float getTop() const;
            float getBottom() const;

            Vector2 getMin() const;
            Vector2 getMax() const;
        };
    }
}

#endif // RECT_H
