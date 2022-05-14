/*
  ==============================================================================

    FilterComponent.h
    Created: 14 May 2022 12:50:42am
    Author:  sooh1

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeId, juce::String cutoffId, juce::String resonanceId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    juce::Label filterLabel;


    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    juce::Label cutoffLabel;
    juce::Label resonanceLabel;

    void setSliderParams(juce::Slider& slider);
    void setSliderLabel(juce::Label& label, juce::String label_name);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
