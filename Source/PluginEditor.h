/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscComponent.h"
#include "AdsrComponent.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class _3OSCsynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    _3OSCsynthAudioProcessorEditor (_3OSCsynthAudioProcessor&);
    ~_3OSCsynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    _3OSCsynthAudioProcessor& audioProcessor;
    OscComponent osc1; 
    OscComponent osc2;
    OscComponent osc3;

    AdsrComponent adsr;

    FilterComponent filter;
    AdsrComponent filterAdsr;

    juce::ImageComponent logo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_3OSCsynthAudioProcessorEditor)
};
