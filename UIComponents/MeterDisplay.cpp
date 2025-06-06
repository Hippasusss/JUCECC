/*
   ==============================================================================

   MeterDisplay.cpp
Created: 8 Mar 2020 6:57:26pm
Author:  Danny Herbert

==============================================================================
*/

#include "MeterDisplay.h"

MeterDisplay::MeterDisplay(Meter* newMeter) :
    meter(newMeter),
    channelCount(newMeter->getNumChannels())
{
    meter->onPrepareCallback = [&]()
    {
        channelCount = meter->getNumChannels();
    };
    startTimerHz(timer_constants::REFRESH_RATE);
    addAndMakeVisible(clipMeter);
    peak.setRate(0.5);
    RMS.setRate(0.5);
    peakHold.setRate(0.5);
    clipMeter.setColour(ToggleButton::ColourIds::tickColourId, colour_constants::red);
    clipMeter.setColour(ToggleButton::ColourIds::tickDisabledColourId, colour_constants::transparent);
}

MeterDisplay::~MeterDisplay()
{
};

void MeterDisplay::paint (Graphics& graphics)
{
    const int separation = 1;
    const int height = getHeight();
    const int width = getWidth();

    auto maincolour = colour_constants::main;
    auto lightmaincolour = colour_constants::lightMain;

    for(int i = 0; i < channelCount; ++i)
    {
        // Get values of various levels
        RMS = meter->getRMS(i);
        peak = meter->getPeak(i);
        if(peak > peakHold)
        {
            peakHold = peak;
            peakHoldTimer = peakHoldTime;
        }

        // Calculate height of each level meter
        const int leftSeparation = i == 0 ? 0 : separation;
        const int rightSeparation = i == channelCount - 1 ? 0 : separation;
        const int scalar = vertical ? height : width;
        const int channelWidth = vertical ? width / channelCount : height / channelCount;

        const int scalarRMS = RMS.getSmoothedValueNormalisedDB() * scalar;
        const int scalarPeakHold = peakHold.getSmoothedValueNormalisedDB() * scalar;
        const int scalarPeak = peak.getSmoothedValueNormalisedDB() * scalar;

        // Vertical
        if(vertical)
        {
            // Draw Peak 
            graphics.setColour(lightmaincolour);
            graphics.fillRect((i * channelWidth) + leftSeparation , height - scalarPeak, channelWidth - leftSeparation- rightSeparation, scalarPeak);
            // Draw RMS
            graphics.setColour(maincolour);
            graphics.fillRect((i * channelWidth) + leftSeparation , height - scalarRMS, channelWidth - leftSeparation - rightSeparation, scalarRMS);
            // Draw Peak Hold
            graphics.drawRect((i * channelWidth) + leftSeparation , height - scalarPeakHold, channelWidth - leftSeparation- rightSeparation, 1);
        }

        // Horizontal
        else if(!vertical)
        {
            // Draw Peak 
            graphics.setColour(lightmaincolour);
            graphics.fillRect(0, i * channelWidth + leftSeparation, scalarPeak, channelWidth - rightSeparation - leftSeparation);
            // Draw RMS
            graphics.setColour(maincolour);
            graphics.fillRect(0, i * channelWidth + leftSeparation, scalarRMS, channelWidth - rightSeparation - leftSeparation);
            // Draw Peak Hold
            graphics.drawRect(scalarPeakHold, i * channelWidth + leftSeparation, 2 , channelWidth - rightSeparation - leftSeparation);
        }
    }

    // Set level readout at top of meter
    const long peakHoldValue = peakHold.getSmoothedValueDBFS();
    const String labelText = peakHoldValue > -60 ? String(peakHoldValue): String("");
    clipMeter.setButtonText(labelText);

    // Set clip indicator
    clip = meter->getClip();
    if (clip)
    {
        clipMeter.setInterceptsMouseClicks(true, true);
        clipMeter.setToggleState(clip, dontSendNotification);
        clipHoldTimer = clipHoldTime;
    }

    // Disallow clicking back on the clip
    else if(!clipMeter.getToggleState())
    {
        clipMeter.setInterceptsMouseClicks(false, false);
    }

}

void MeterDisplay::resized() 
{
    vertical = getHeight() > getWidth();
    const size_t clipSize = 14;
    if(vertical)
    {
        clipMeter.setBounds(0,0, getWidth(), clipSize);
    }
    else
    {
        clipMeter.setBounds(getWidth() - clipSize,0, clipSize, getHeight());
    }
}

void MeterDisplay::setMeter(Meter* meter)
{
    this->meter = meter;
}

void MeterDisplay::timerCallback()
{
    if(peakHoldTimer > 0)
    {
        peakHoldTimer -= 1000 / timer_constants::REFRESH_RATE;
    }
    else
    {
        peakHold = peak;
    }

    if(clipHoldTime > 0)
    {
        clipHoldTimer -= 1000 / timer_constants::REFRESH_RATE;
    }
    else
    {
        clipMeter.setToggleState(false, dontSendNotification);
        clip = false;;
    }
    repaint();
}


