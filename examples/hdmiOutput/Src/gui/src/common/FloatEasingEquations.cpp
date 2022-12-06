#include <gui/common/FloatEasingEquations.hpp>

FloatEasingEquations::FloatEasingEquations()
{
}

float FloatEasingEquations::floatCubicEaseIn(float t, float b, float c, float d)
{
    t /= d;
    return c * t * t * t + b;
}

float FloatEasingEquations::floatCubicEaseOut(float t, float b, float c, float d)
{
    t /= d;
    t--;
    return c * (t * t * t + 1) + b;
}

float FloatEasingEquations::floatCubicEaseInOut(float t, float b, float c, float d)
{
    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t * t + b;
    }
    t -= 2;
    return c / 2 * (t * t * t + 2) + b;
}

float FloatEasingEquations::floatBackEaseOut(float t, float b, float c, float d)
{
    float s = 1.70158f;
    t = t / d - 1;
    return c * (t * t * ((s + 1) * t + s) + 1) + b;
}
