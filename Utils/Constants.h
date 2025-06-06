/*
  ==============================================================================

    Constants.cpp
    Created: 27 Feb 2020 9:17:19pm
    Author:  Danny Herbert

  ==============================================================================
*/


#pragma once
#include "juce_core/juce_core.h"
#include "juce_graphics/juce_graphics.h"

using namespace juce;

namespace parameter_constants
{
	const String INPUT_GAIN_ID = "inputGain";
	const String OUTPUT_GAIN_ID = "outputGain";
	const String DRIVE_ID = "drive";
	const String FREQUENCY_ID = "frequency";
	const String RESONANCE_ID = "resonance";
	const String MIX_ID = "mix";
	const String ENV_SPEED_ID = "envSpeed";
	const String ENV_ATTACK_ID = "envAttack";
	const String ENV_RELEASE_ID = "envRelease";
	const String ENV_ADVANCED_ID= "envAdvanced";
	const String TWO_FOUR_POLE_ID = "twoFourPole";
	const String ENV_AMOUNT_ID = "envAmount";
}
namespace timer_constants 
{
	const int REFRESH_RATE = 60;
}

namespace colour_constants
{
	const Colour main = Colours::lightblue;
	const Colour lightMain = juce::Colour(0xffe0f4ff);
	const Colour backGround = Colours::white;
	const Colour red = Colours::salmon;
	const Colour transparent = Colours::transparentBlack;
}
