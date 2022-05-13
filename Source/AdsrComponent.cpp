/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 13 May 2022 9:21:10pm
    Author:  sooh1

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
   
    //set label 
    setSliderLabel(attackLabel, "A");
    setSliderLabel(decayLabel, "D");
    setSliderLabel(sustainLabel, "S");
    setSliderLabel(releaseLabel, "R");

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(49, 55, 59));
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(40, 44, 49));
    g.fillRoundedRectangle(bounds.toFloat(), 5.0f);

    g.setColour(juce::Colour::fromRGB(209, 214, 218));
    g.setFont(15.0f);
    g.drawText("Envelope", 5, 10, 100, 25, juce::Justification::centred);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 35 ;
    const auto sliderStartX = 10;
    const auto sliderStartY = 25;
    const auto labelHeight = 10;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    attackLabel.setBounds(attackSlider.getX(), attackSlider.getBottom()+5, sliderWidth, labelHeight);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getBottom()+5, sliderWidth, labelHeight);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getBottom()+5, sliderWidth, labelHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getBottom()+5, sliderWidth, labelHeight);


}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

void AdsrComponent::setSliderLabel(juce::Label& label, juce::String label_name)
{
    label.setFont(13.0f);
    label.setText(label_name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);


}