/*
  ==============================================================================

    FilterComponent.cpp
    Created: 14 May 2022 12:50:42am
    Author:  sooh1

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeId, juce::String cutoffId, juce::String resonanceId)
{
    //Filter type select
    juce::StringArray filterTypeChoices{ "Low Pass", "Band Pass", "High Pass" };
    filterTypeSelector.addItemList(filterTypeChoices, 1);
    filterTypeSelector.setSelectedItemIndex(0);
    addAndMakeVisible(filterTypeSelector);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeId, filterTypeSelector);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, cutoffId, cutoffSlider);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, resonanceId, resonanceSlider);



    setSliderParams(cutoffSlider);
    setSliderParams(resonanceSlider);
    
    //set label 
    setSliderLabel(cutoffLabel, "cut-off");
    setSliderLabel(resonanceLabel, "resonance");
    
    filterLabel.setFont(16.0f);
    filterLabel.setText("Filter",  juce::dontSendNotification);
    filterLabel.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(filterLabel);




}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(49, 55, 59));
    auto bounds = getLocalBounds();
    g.setColour(juce::Colour::fromRGB(40, 44, 49));
    g.fillRoundedRectangle(bounds.toFloat(), 5.0f);

    
}

void FilterComponent::resized()
{
    const auto startX = 18;
    const auto startY = 80;
    const auto width = 70;
    const auto height = 88;

    filterTypeSelector.setBounds(18, 40, 145, 25);
    cutoffSlider.setBounds(filterTypeSelector.getX(), filterTypeSelector.getBottom(), width, height);
    resonanceSlider.setBounds(filterTypeSelector.getRight()-10, filterTypeSelector.getBottom(), width, height);

    cutoffLabel.setBounds(startX, cutoffSlider.getBottom()+5, width, 10); 
    resonanceLabel.setBounds(filterTypeSelector.getRight()-10, resonanceSlider.getBottom()+5, width, 10);

    
    filterLabel.setBounds(10, 10, 145, 25);

}


void FilterComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

void FilterComponent::setSliderLabel(juce::Label& label, juce::String label_name)
{
    label.setFont(13.0f);
    label.setText(label_name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);


}