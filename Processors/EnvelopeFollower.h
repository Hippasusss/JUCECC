/*
   ==============================================================================

   EnvelopeFollower.h
Created: 22 Feb 2020 2:39:50pm
Author:  Danny Herbert

==============================================================================
*/

#pragma once
#include "juce_dsp/juce_dsp.h"
#include "RingBuffer.h"

using namespace juce;

class EnvelopeFollower: dsp::ProcessorBase
{

public:
    EnvelopeFollower();
    ~EnvelopeFollower();

    void process(const dsp::ProcessContextReplacing<float>&) override;
    void prepare(const dsp::ProcessSpec&) override;
    void reset() override;

    void setAttack(float milliseconds);
    void setRelease(float milliseconds);
    void setAmount(float newAmount);
    const std::vector<float>& getEnvelope() const;
    RingBufferVector<float> envelopeDisplayData;

private:
    double sampleRate;
    unsigned int numChannels;
    unsigned int maxBlockSize;

    float amount;
    float attackTime, releaseTime;
    float attackAlpha, releaseAlpha;

    std::vector<float> envelopeOutput;
    std::vector<float> envelopeState;
};

