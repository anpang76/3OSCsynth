/*
  ==============================================================================

    SynthSound.h
    Created: 11 May 2022 8:11:32pm
    Author:  sooh1

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
  // A class interacts with midi note and channel and allows more than one SyntesiserVoice to play the same sound at the same time
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};