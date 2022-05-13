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

//==============================================================================
/**
*/
class _3OSCsynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    _3OSCsynthAudioProcessorEditor (_3OSCsynthAudioProcessor&);
    ~_3OSCsynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _3OSCsynthAudioProcessor& audioProcessor;
    OscComponent osc1; 
    OscComponent osc2;
    OscComponent osc3;
    AdsrComponent adsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_3OSCsynthAudioProcessorEditor)
};
