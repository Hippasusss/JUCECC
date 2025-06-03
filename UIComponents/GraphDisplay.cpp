/*
  ==============================================================================

	GraphDisplay.cpp
	Created: 3 Mar 2020 11:27:17pm
	Author:  Danny Herbert

  ==============================================================================
*/

#include "GraphDisplay.h"
#include "Constants.h"

//==============================================================================

GraphDisplay::GraphDisplay(std::initializer_list<DisplayData<float>> displayDatas) :
    displayDatas(displayDatas)
{
	startTimerHz(timer_constants::REFRESH_RATE);
}
GraphDisplay::~GraphDisplay() = default;


void GraphDisplay::drawPath(Graphics& graphics, const DisplayData<float>& data)
{
    const bool shouldFill =  data.getShouldFill();
    graphics.setColour(data.getColour());
    
    auto previousValues = data.getPreviousValues();
    const int width = getBounds().getWidth();
    const int height = getBounds().getHeight();
    const int numPoints = previousValues.size();
    const float segmentWidth = static_cast<float>(width) / numPoints;

    Path path;
    path.preallocateSpace(numPoints * 3 + (shouldFill ? 4 : 0));
    
    if (shouldFill) {
        path.startNewSubPath(0, height);
    } else {
        path.startNewSubPath(0, height - (previousValues[0] * height));
    }

    for (int i = shouldFill ? 0 : 1; i < numPoints; i++) {
        path.lineTo(i * segmentWidth, height - (previousValues[i] * height));
    }

    if (shouldFill) {
        path.lineTo(width, height);
        path.closeSubPath();
        graphics.fillPath(path);
    } else {
        PathStrokeType stroke(data.getStrokeThickness());
        stroke.setEndStyle(PathStrokeType::rounded);
        graphics.strokePath(path, stroke);
    }
}

void GraphDisplay::paint(Graphics& graphics)
{
    for (auto& displayData : displayDatas) 
    {
        drawPath(graphics, displayData);
    }
}

void GraphDisplay::resized()
{
}

void GraphDisplay::timerCallback()
{
    for (auto& displayData : displayDatas) 
    {
        displayData.updateValues();
    }
	repaint();
}






