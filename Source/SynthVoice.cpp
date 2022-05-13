/*
  ==============================================================================

    SynthVoice.cpp
    Created: 11 May 2022 8:11:24pm
    Author:  sooh1

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    for (int i = 0; i < 2; i++)
    {
        osc1[i].setFreq(midiNoteNumber);
        osc2[i].setFreq(midiNoteNumber);
        osc3[i].setFreq(midiNoteNumber);
       
    }

    adsr.noteOn();

}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();

    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {
        osc1[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        osc2[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        osc3[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
      
    }
    
    gain.prepare(spec);
    gain.setGainLinear(0.07f);

    isPrepared = true;

}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    //Calling voices 
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(),numSamples, false, false,true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    
    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc1[ch].processNextSample(buffer[s])+osc2[ch].processNextSample(buffer[s])+osc3[ch].processNextSample(buffer[s]);
        }
    }
    
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (!adsr.isActive())
            clearCurrentNote();
    }

}

void SynthVoice::reset()
{
    gain.reset();
    adsr.reset();
}