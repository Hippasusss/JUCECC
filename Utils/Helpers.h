
/*
   ==============================================================================

   Helpers.h
   Created: 9 Mar 2020 11:51:32am
   Author:  Danny Herbert

   ==============================================================================
*/
#pragma once
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_dsp/juce_dsp.h"
#include "juce_graphics/juce_graphics.h"
using namespace juce;

namespace AudioHelpers
{

template<typename SampleType> 
void copyAbsoluteIntoBlock(const dsp::AudioBlock<SampleType>& inputBlock, dsp::AudioBlock<SampleType>& outputBlock) 
{
    jassert(inputBlock.getNumChannels() == outputBlock.getNumChannels());
    jassert(inputBlock.getNumSamples() == outputBlock.getNumSamples());

    for(auto i = 0; i < inputBlock.getNumChannels(); ++i) 
    {
        const auto inputChan = inputBlock.getChannelPointer(i);
        const auto outputChan = outputBlock.getChannelPointer(i);
        for(auto j = 0; j < inputBlock.getNumSamples(); ++j) 
        {
            outputChan[j] = abs(inputChan[j]);
        }
    }
}

template<typename SampleType> 
SampleType getAverageMagnitude(const dsp::AudioBlock<SampleType>& block) 
{
    SampleType sum {0};
    const auto numChannels = block.getNumChannels();
    const auto blockSize = block.getNumSamples();

    for(auto i = 0; i < numChannels; ++i) 
    {
        const auto chan = block.getChannelPointer(i);
        for(auto j = 0; j < blockSize; ++j) 
        {
            sum += abs(chan[j]);
        }
    }
    return sum / (blockSize * numChannels);
}

template<typename SampleType>
SampleType getPeakMagnitude(const dsp::AudioBlock<SampleType>& block) 
{
    SampleType value {};
    const auto numChannels = block.getNumChannels();
    const auto blockSize = block.getNumSamples();

    for(auto i = 0; i < numChannels; ++i) 
    {
        const auto chan = block.getChannelPointer(i);
        for(auto j = 0; j < blockSize; ++j) 
        {
            const SampleType sample = abs(chan[j]);
            value = sample > value ? sample : value;
        }
    }
    return value;
}

template<typename ValueType>
ValueType getNormalisedDB(ValueType value, ValueType dbMinusInfinity = -100) 
{
    return jlimit<ValueType>(0.0f, 1.0f, 
                             ((ValueType(20.0) * std::log10f(abs(value)) / ValueType(-dbMinusInfinity)) + 1));
}

template<typename SampleType> 
SampleType getAverageMagnitude(const AudioBuffer<SampleType>& buffer) 
{
    SampleType sum {0};
    const auto numChannels = buffer.getNumChannels();
    const auto numSamples = buffer.getNumSamples();

    for(auto i = 0; i < numChannels; ++i) 
    {
        const auto chan = buffer.getReadPointer(i);
        for(auto j = 0; j < numSamples; ++j) 
        {
            sum += abs(chan[j]);
        }
    }
    return sum / (numSamples * numChannels);
}

template<typename SampleType>
void copyAudioBlockIntoBuffer(const dsp::AudioBlock<const SampleType>& sourceBlock,
                           AudioBuffer<SampleType>& destinationBuffer,
                           const size_t numSamples,
                           const size_t sourceStartSample = 0,
                           const size_t destStartSample = 0) {
    jassert(sourceBlock.getNumChannels() == destinationBuffer.getNumChannels());
    for(auto channel = 0; channel < destinationBuffer.getNumChannels(); ++channel) 
    {
        auto* channelPointer = sourceBlock.getChannelPointer(channel);
        channelPointer += sourceStartSample;
        destinationBuffer.copyFrom(channel, destStartSample, channelPointer, numSamples);
    }
}

template<typename SampleType>
void sumAndAverageChannels(AudioBuffer<SampleType>& buffer) 
{
    const size_t numChannels = buffer.getNumChannels();
    const size_t numSamples = buffer.getNumSamples();
    auto* const dataChannelWrite = buffer.getWritePointer(0);

    for (size_t i = 1; i < numChannels; ++i) 
    {
        const auto* const dataChannelRead = buffer.getReadPointer(i);
        for (size_t j = 0; j < numSamples; ++j) 
        {
            dataChannelWrite[j] += dataChannelRead[j];
        }
    }

    for (size_t i = 0; i < numSamples; ++i) 
    {
        dataChannelWrite[i] /= numChannels;
    }
}
}



namespace LayoutHelpers 
{

template<typename ComponentType, size_t arraySize>
void distributeHorizontally(std::array<ComponentType*, arraySize> components, 
                            Rectangle<int>& bounds, 
                            size_t reduction = 0) 
{
    const size_t componentWidth = bounds.getWidth() / arraySize;
    for(auto* component : components) 
    {
        component->setBounds(bounds.removeFromLeft(componentWidth).reduced(reduction));
    }
}

template<typename ComponentType, size_t arraySize>
void distributeVertically(std::array<ComponentType*, arraySize> components, 
                          Rectangle<int>& bounds, 
                          size_t reduction = 0) 
{
    const size_t componentHeight = bounds.getHeight() / arraySize;
    for(auto* component : components) 
    {
        component->setBounds(bounds.removeFromTop(componentHeight).reduced(reduction));
    }
}
}

