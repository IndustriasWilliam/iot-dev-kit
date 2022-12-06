#ifndef FLOATEASINGEQUATIONS_HPP
#define FLOATEASINGEQUATIONS_HPP

class FloatEasingEquations
{
public:
    FloatEasingEquations();
    ~FloatEasingEquations() { }

    static float floatCubicEaseIn(float t, float b, float c, float d);
    static float floatCubicEaseOut(float t, float b, float c, float d);
    static float floatCubicEaseInOut(float t, float b, float c, float d);
    static float floatBackEaseOut(float t, float b, float c, float d);

private:
};

#endif // FLOATEASINGEQUATIONS_HPP
