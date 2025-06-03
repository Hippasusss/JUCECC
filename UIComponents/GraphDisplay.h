/*
   ==============================================================================

   GraphDisplay.h
Created: 3 Mar 2020 11:27:17pm
Author:  Danny Herbert

==============================================================================
*/

#pragma once

#include "DisplayData.h"

#include "juce_gui_basics/juce_gui_basics.h"
#include <initializer_list>



class GraphDisplay : public Component,
	public Timer
{
public:
	GraphDisplay(std::initializer_list<DisplayData<float>> displayDatas);
	~GraphDisplay();

    void drawPath(Graphics& graphics, const DisplayData<float>& data);


	void paint(Graphics&) override;
	void timerCallback() override;
	void resized() override;

private:
    std::vector<DisplayData<float>> displayDatas;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphDisplay)
};
