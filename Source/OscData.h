/*
  ==============================================================================

    OscData.h
    Created: 11 May 2022 10:29:29pm
    Author:  sooh1

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setType(const int oscSelection);
    void setGain(const float levelInDecibels);
    void setOscPitch(const int pitch);
    void setFreq(const int midiNoteNumber);
    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    float processNextSample(float input);
    void setParams(const int oscChoice, const float oscGain, const int oscPitch);
    void resetAll();

private:
    juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain;
    int lastPitch{ 0 };
    int lastMidiNote{ 0 };
};