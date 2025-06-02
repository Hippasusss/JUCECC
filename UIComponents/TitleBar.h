/*
  ==============================================================================

    TitleBar.h
    Created: 13 Jan 2022 1:07:07am
    Author:  Danny Herbert

  ==============================================================================
*/

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "CustomLookAndFeel.h"
using namespace juce;

//==============================================================================
/*
*/
class TitleBar  : public juce::Component
{
public:
    TitleBar(const String& name);
    ~TitleBar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    String name;
    CustomLookAndFeel lookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleBar)
};
