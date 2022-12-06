#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void modelUpdateMCU(uint16_t mcu) {}
    virtual void modelUpdateFPS(uint16_t fps) {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
