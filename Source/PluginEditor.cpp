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
    , adsr(audioProcessor.apvts, "Envelope", "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE")
    , filterAdsr(audioProcessor.apvts,"Filter Envelope", "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
{
   //adding logo

    auto logoImage = juce::ImageCache::getFromMemory(BinaryData::Logo_png, BinaryData::Logo_pngSize);
    
    if (logoImage.isValid())
        logo.setImage(logoImage, juce::RectanglePlacement::stretchToFit);
    else
        jassertfalse;



  
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(logo);

   

    setSize(830, 500);
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
    filter.setBounds(10, osc1.getBottom() + 15, oscWidth, oscHeight+50);
    filterAdsr.setBounds(osc1.getRight() + 15, osc1.getBottom() + 15, oscWidth, oscHeight * 2);

    logo.setBounds(10, filter.getBottom(), oscWidth, 90);
}
