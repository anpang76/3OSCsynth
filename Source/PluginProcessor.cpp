/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_3OSCsynthAudioProcessor::_3OSCsynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());

   
    //synth.addVoice(new SynthVoice());
    for (int i = 0; i < 5; i++)
    {
        synth.addVoice(new SynthVoice());
    }
   

}

_3OSCsynthAudioProcessor::~_3OSCsynthAudioProcessor()
{
}

//==============================================================================
const juce::String _3OSCsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool _3OSCsynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _3OSCsynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _3OSCsynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double _3OSCsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _3OSCsynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _3OSCsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void _3OSCsynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String _3OSCsynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void _3OSCsynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void _3OSCsynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
}

void _3OSCsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool _3OSCsynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void _3OSCsynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //to avoid people getting screaming feedback
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    setParams();
    //rendering the voice by synth
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool _3OSCsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* _3OSCsynthAudioProcessor::createEditor()
{
    return new _3OSCsynthAudioProcessorEditor (*this);
}

//==============================================================================
void _3OSCsynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void _3OSCsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _3OSCsynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout _3OSCsynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // OSC select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1", "Oscillator 1", juce::StringArray{ "Sine", "Saw", "Square" ,"Triangle"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2", "Oscillator 2", juce::StringArray{ "Sine", "Saw", "Square" ,"Triangle"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC3", "Oscillator 3", juce::StringArray{ "Sine", "Saw", "Square" ,"Triangle"}, 0));
    
    // OSC Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3GAIN", "Oscillator 3 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));

    // OSC Pitch
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch", -48, 48, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator 2 Pitch", -48, 48, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC3PITCH", "Oscillator 3 Pitch", -48, 48, 0));

    //AMP ADSR 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    //Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "Low Pass", "Band Pass", "High Pass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 20000.0f, "Hz"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "Filter Resonance", juce::NormalisableRange<float> { 0.1f, 2.0f, 0.1f }, 0.1f, ""));

    //Filter ADSR 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERADSRDEPTH", "Filter ADSR Depth", juce::NormalisableRange<float> { 0.0f, 10000.0f, 0.1f, 0.3f }, 10000.0f, ""));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERATTACK", "Filter Attack", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERDECAY", "Filter Decay", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERSUSTAIN", "Filter Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRELEASE", "Filter Release", juce::NormalisableRange<float> { 0.0f, 3.0f, 0.1f }, 0.1f));

    return { params.begin(), params.end() };

}

void _3OSCsynthAudioProcessor::setParams()
{
    setVoiceParams();
    setFilterParams();
}

void _3OSCsynthAudioProcessor::setVoiceParams()
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {   
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& osc1Choice = *apvts.getRawParameterValue("OSC1");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& osc1Pitch = *apvts.getRawParameterValue("OSC1PITCH");

            auto& osc2Choice = *apvts.getRawParameterValue("OSC2");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& osc2Pitch = *apvts.getRawParameterValue("OSC2PITCH");

            auto& osc3Choice = *apvts.getRawParameterValue("OSC3");
            auto& osc3Gain = *apvts.getRawParameterValue("OSC3GAIN");
            auto& osc3Pitch = *apvts.getRawParameterValue("OSC3PITCH");

            auto& filterAttack = *apvts.getRawParameterValue("FILTERATTACK");
            auto& filterDecay = *apvts.getRawParameterValue("FILTERDECAY");
            auto& filterSustain = *apvts.getRawParameterValue("FILTERSUSTAIN");
            auto& filterRelease = *apvts.getRawParameterValue("FILTERRELEASE");

            auto& osc1 = voice->getOscillator1();
            auto& osc2 = voice->getOscillator2();
            auto& osc3 = voice->getOscillator3();

            auto& adsr = voice->getAdsr();
            auto& filterAdsr = voice->getFilterAdsr();
            
            for (int i = 0; i < getTotalNumOutputChannels(); i++)
            {
                osc1[i].setParams(osc1Choice, osc1Gain, osc1Pitch);
                osc2[i].setParams(osc2Choice, osc2Gain, osc2Pitch);
                osc3[i].setParams(osc3Choice, osc3Gain, osc3Pitch);
            }
            
            adsr.updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            filterAdsr.updateADSR(filterAttack.load(), filterDecay.load(), filterSustain.load(), filterRelease.load());
        }
    }
}

void _3OSCsynthAudioProcessor::setFilterParams()
{
    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& filterCutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto& filterResonance = *apvts.getRawParameterValue("FILTERRESONANCE");
    auto& adsrDepth = *apvts.getRawParameterValue("FILTERADSRDEPTH");

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->updateModParams(filterType, filterCutoff, filterResonance, adsrDepth);
        }
    }

}