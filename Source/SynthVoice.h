/*
  ==============================================================================

    SynthVoice.h
    Created: 11 May 2022 8:11:24pm
    Author:  sooh1

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "OscData.h"
#include "AdsrData.h"
#include "FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
    void reset();

    std::array<OscData, 3>& getOscillator1() { return osc1; }
    std::array<OscData, 3>& getOscillator2() { return osc2; }
    std::array<OscData, 3>& getOscillator3() { return osc3; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return filterAdsr; }
    
    float getFilterAdsrOutput() { return filterAdsrOutput; }
    void updateModParams(const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth);

private:
    static constexpr int numChannelsToProcess{ 3 };
    std::array<OscData, numChannelsToProcess> osc1;
    std::array<OscData, numChannelsToProcess> osc2;
    std::array<OscData, numChannelsToProcess> osc3;
    std::array<FilterData, numChannelsToProcess> filter;

    AdsrData adsr;
    AdsrData filterAdsr;
    float filterAdsrOutput{ 0.0f };

    juce::AudioBuffer<float> synthBuffer;
    juce::dsp::Gain<float> gain;
    
    bool isPrepared{ false };
};

