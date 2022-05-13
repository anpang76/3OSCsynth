/*
  ==============================================================================

    FilterData.h
    Created: 14 May 2022 12:50:48am
    Author:  sooh1

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscData.h"

class FilterData : public juce::dsp::StateVariableTPTFilter<float>
{
public :
    FilterData();
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setParams(const int filterType, const float filterCutoff, const float filterResonance);
    void processNextBlock(juce::AudioBuffer<float>& buffer);
    float processNextSample(int channel, float inputValue);
    void resetAll();


private :
    void selectFilterType(const int type);
};