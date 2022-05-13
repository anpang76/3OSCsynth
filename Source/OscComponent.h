/*
  ==============================================================================

    OscComponent.h
    Created: 11 May 2022 10:29:54pm
    Author:  sooh1

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId);
    ~OscComponent() override;
  
    void paint (juce::Graphics&) override;
    void resized() override;
    
   
private:
    juce::ComboBox oscSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    juce::Label oscLabel;

    juce::Slider gainSlider;
    juce::Label gainLabel;
    juce::Slider pitchSlider;
    juce::Label pitchLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchAttachment;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
