/*
  ==============================================================================

    OscData.cpp
    Created: 11 May 2022 10:29:29pm
    Author:  sooh1

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    prepare(spec);
    osc.prepare(spec);
    gain.prepare(spec);

}
void OscData::setType(const int oscSelection)
{
    switch (oscSelection)
    {
        //Sine
    case 0:
        initialise([](float x) {return std::sin(x); });
        break;

        //Saw
    case 1:
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
        break;

        //Square
    case 2: 
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;

        //Triangle
    case 3:
        initialise([](float x) { return abs(x / juce::MathConstants<float>::pi);});
        break;
    
    default:
        jassertfalse;
        break;
    }
}

void OscData::setGain(const float levelInDecibels)
{
    gain.setGainDecibels(levelInDecibels);
}
void OscData::setOscPitch(const int pitch)
{
    lastPitch = pitch;
    setFreq(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + lastPitch));
    
}
void OscData::setFreq(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    lastMidiNote = midiNoteNumber;
}

void OscData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert(audioBlock.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}
float OscData::processNextSample(float input)
{
    return gain.processSample(processSample(input));
}
void OscData::setParams(const int oscChoice, const float oscGain, const int oscPitch)
{
    setType(oscChoice);
    setGain(oscGain);
    setOscPitch(oscPitch);
}
void OscData::resetAll()
{
    reset();
    osc.reset();
    gain.reset();
}
