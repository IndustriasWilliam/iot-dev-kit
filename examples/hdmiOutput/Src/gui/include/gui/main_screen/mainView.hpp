#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/mainViewBase.hpp>
#include <gui/main_screen/mainPresenter.hpp>

#include <gui/Transitions/FlipTransition.hpp>
#include <gui/Transitions/CoverTransition.hpp>
#include <gui/Transitions/SlideTransition.hpp>
#include <gui/Transitions/CurtainsTransition.hpp>
#include <gui/Transitions/RolloutTransition.hpp>
#include <gui/Transitions/CubeTransition.hpp>
#include <gui/Transitions/SpinOutTransition.hpp>
#include <gui/Transitions/SpinTransition.hpp>

class mainView : public mainViewBase
{
public:
    mainView();
    virtual ~mainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleTickEvent();

    virtual void startTransitionPressed();
    virtual void getTransitionInfo(TransitionInfo* value);
    virtual void scrollWheelPressed();
    virtual void scrollWheelAnimationEnded();
    virtual void ChromARTPressed(bool value);
    virtual void sliderMenuStateChanged(SlideMenu::State value);
    virtual void animationSpeedButtonPressed(bool value);

    void updateMCU(uint16_t mcu);
    void updateFPS(uint16_t fps);

protected:

    enum BackgroundState
    {
        DAY,
        NIGHT
    } currentBackground;

    Callback<mainView, uint16_t> transitionEndedCallback;
    void transitionEndedHandler(uint16_t newBackgroundId);

    Callback<mainView, const FadeAnimator<Button>&> buttonFadeAnimationEndedCallback;
    void buttonFadeAnimationEndedHandler(const FadeAnimator<Button>& src);

    bool transitionInProgress;
    uint16_t transitionSpeed;

    Transitions* transitions[Transitions::NUMBER_OF_TRANSITIONS];
    FlipTransition flip;
    CoverTransition cover;
    SlideTransition slide;
    CurtainsTransition curtains;
    RolloutTransition rollout;
    CubeTransition cube;
    SpinOutTransition spinout;
    SpinTransition spin;

    int8_t fadeDirection;

    uint16_t tickCounter;
    uint16_t transitionMenuTimeoutCounter;

    int16_t frameSkippedCounter;
    int16_t frames;
    int16_t fps;
    uint16_t previousMcuLoadPct;
};

#endif // MAINVIEW_HPP
