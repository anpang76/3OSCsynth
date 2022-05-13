/*
  ==============================================================================

    OscComponent.cpp
    Created: 11 May 2022 10:29:54pm
    Author:  sooh1

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId)
{   
    juce::StringArray oscChoices{ "Sine", "Saw", "Square","Triangle"};
    oscSelector.addItemList(oscChoices, 1);
    oscSelector.setSelectedItemIndex(0);
    addAndMakeVisible(oscSelector);
  
    //Gain Slider 
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(gainSlider);

    //Pitch Slider 
    pitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(pitchSlider);

    //Attachment 
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscSelector);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);
    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, pitchId, pitchSlider);

   //label
    gainLabel.setFont(13.0f);
    gainLabel.setText("gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    pitchLabel.setFont(13.0f);
    pitchLabel.setText("pitch", juce::dontSendNotification);
    pitchLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(pitchLabel);
    
    oscLabel.setFont(15.0f);
    oscLabel.setText(oscId, juce::dontSendNotification);
    oscLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(oscLabel);


}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
   
    g.fillAll(juce::Colour::fromRGB(49, 55, 59));
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(40, 44, 49));
    g.fillRoundedRectangle(bounds.toFloat(), 5.0f);
}

void OscComponent::resized()
{
    const auto yStart = 25;
    const auto width = 70;
    const auto height = 88;

    oscLabel.setBounds(0,10,width, height/4);
    oscSelector.setBounds(18, 40, 100, 25); 
    gainSlider.setBounds(120, yStart, width, height);
    pitchSlider.setBounds(190, yStart, width, height);

    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY()-50, gainSlider.getWidth(), gainSlider.getHeight());
    pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getY()-50, pitchSlider.getWidth(), pitchSlider.getHeight());


}

