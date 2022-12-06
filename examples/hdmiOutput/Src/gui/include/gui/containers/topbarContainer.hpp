#ifndef TOPBARCONTAINER_HPP
#define TOPBARCONTAINER_HPP

#include <gui_generated/containers/topbarContainerBase.hpp>

class topbarContainer : public topbarContainerBase
{
public:
    topbarContainer();
    virtual ~topbarContainer() {}

    virtual void initialize();

    virtual void chromARTStateChangedAction(bool state);

    void updateMCU(uint16_t value);
    void updateFPS(uint16_t value);
protected:

};

#endif // TOPBARCONTAINER_HPP
