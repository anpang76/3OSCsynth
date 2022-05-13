/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
_3OSCsynthAudioProcessorEditor::_3OSCsynthAudioProcessorEditor (_3OSCsynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , osc1(audioProcessor.apvts, "OSC1","OSC1GAIN","OSC1PITCH")
    , osc2(audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH")
    , osc3(audioProcessor.apvts, "OSC3", "OSC3GAIN", "OSC3PITCH")
    , adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(adsr);
    

    setSize(830, 630);
}

_3OSCsynthAudioProcessorEditor::~_3OSCsynthAudioProcessorEditor()
{
}

//==============================================================================
void _3OSCsynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(49, 55, 59));
    auto total_bounds = getLocalBounds();
    g.setColour(juce::Colours::black);
    g.drawRect(total_bounds.toFloat());
   
}

void _3OSCsynthAudioProcessorEditor::resized()
{
    const auto oscWidth = 260;
    const auto oscHeight = 130;
    const auto posy = 50;
    osc1.setBounds(10, posy, oscWidth, oscHeight);
    osc2.setBounds(osc1.getRight() + 15, posy, oscWidth, oscHeight);
    osc3.setBounds(osc2.getRight() + 15, posy, oscWidth, oscHeight);
    adsr.setBounds(osc3.getX(), osc1.getBottom()+15, oscWidth, oscHeight*2);
}
