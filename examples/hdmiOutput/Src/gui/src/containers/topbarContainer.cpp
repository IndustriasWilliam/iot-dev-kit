#include <gui/containers/topbarContainer.hpp>
#include "gui/common/constans.hpp"

topbarContainer::topbarContainer()
{

}

void topbarContainer::initialize()
{
    topbarContainerBase::initialize();

    if (chromArtButton.getState())
    {
        chromArtGradient.startFadeAnimation(255, CHROM_ART_GRADIENT_FADE_DURATION);
    }
}

void topbarContainer::chromARTStateChangedAction(bool state)
{
    if (state)
    {
        chromArtGradient.startFadeAnimation(255, CHROM_ART_GRADIENT_FADE_DURATION);
    }
    else
    {
        chromArtGradient.startFadeAnimation(0, CHROM_ART_GRADIENT_FADE_DURATION);
    }
}

void topbarContainer::updateMCU(uint16_t value)
{
    Unicode::snprintf(mcuValueBuffer, MCUVALUE_SIZE, "%d", value);
    mcuValue.invalidate();
}

void topbarContainer::updateFPS(uint16_t value)
{
    Unicode::snprintf(fpsValueBuffer, FPSVALUE_SIZE, "%d", value);
    fpsValue.invalidate();
}
