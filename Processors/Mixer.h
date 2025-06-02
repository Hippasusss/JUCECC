/*
  ==============================================================================

    Mixer.h
    Created: 8 Mar 2020 11:49:53am
    Author:  Danny Herbert

  ==============================================================================
*/
#pragma once
#include "juce_dsp/juce_dsp.h"

using namespace juce;

class Mixer : dsp::ProcessorBase
{
public:
    Mixer();
    Mixer(dsp::AudioBlock<float>* other);
    void prepare(const dsp::ProcessSpec&) override;
    void process(const dsp::ProcessContextReplacing<float>&) override;
    void reset() override;
    void setOtherBlock(const dsp::AudioBlock<float>* other);
    void setMix(float value);

private:
    const dsp::AudioBlock<float>* otherBlock;
    int numChannels; 
    int maxBlockSize;
    float mix;

 };
