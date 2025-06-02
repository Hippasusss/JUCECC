/*
  ==============================================================================

    BufferStore.h
    Created: 8 Mar 2020 4:40:40pm
    Author:  Danny Herbert

  ==============================================================================
*/

#pragma once
#include "juce_dsp/juce_dsp.h"

using namespace juce;


 class BufferStore : dsp::ProcessorBase
 {
 public:
	 BufferStore();
	 ~BufferStore() = default;
	 void prepare(const dsp::ProcessSpec&) override;
	 void process(const dsp::ProcessContextReplacing<float>&) override;
	 void reset() override;

 	 const dsp::AudioBlock<float>* getAudioBlockPointer();

 private:
    dsp::AudioBlock<float> block;
    AudioBuffer<float> buffer;

 };
