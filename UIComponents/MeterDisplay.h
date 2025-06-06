/*
   ==============================================================================

MeterDisplay.h
Created: 8 Mar 2020 6:57:26pm
Author:  Danny Herbert

==============================================================================
*/

#pragma once
#include "juce_gui_basics/juce_gui_basics.h"

#include "LevelValueDisplay.h"
#include "Meter.h"
using namespace juce;

//==============================================================================
/*
*/
class MeterDisplay    : public Component,
    public Timer
{
public: void timerCallback() override;
    enum ColourIds
    {
    };

    MeterDisplay(Meter* newMeter);
    ~MeterDisplay();

    void paint (Graphics&) override;
    void resized() override;
    void setMeter(Meter* newMeter);

private:
    Meter* meter;
    ToggleButton clipMeter;

    const float rate = 0.15f;
    const int clipHoldTime = 3000;
    const int peakHoldTime = 1500;

    int channelCount = 0;
    bool clip = false;
    bool vertical = false;
    int clipHoldTimer = 0;
    int peakHoldTimer = 0;

    LevelValueDisplay<float> peak;
    LevelValueDisplay<float> peakHold;
    LevelValueDisplay<float> RMS;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterDisplay)
};
