/* Copyright 2018-2019 Tobias Hienzsch
 *
 * modEQ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * modEQ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with modEQ. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// JUCE
#include "../JuceLibraryCode/JuceHeader.h"

// tobanteAudio
#include "analyser/spectrum_analyser.h"
#include "parameters/text_value_converter.h"
#include "processor/equalizer_processor.h"
#include "processor/modulation_source_processor.h"

/**
 * @brief Entry point for processor thread. Inherites from juce::AudioProcessor
 */
class ModEQProcessor : public AudioProcessor,
                       public AudioProcessorValueTreeState::Listener,
                       public ChangeBroadcaster
{
private:
    UndoManager undo;
    AudioProcessorValueTreeState state;

public:
    ModEQProcessor();
    ~ModEQProcessor() override = default;

    void prepareToPlay(double newSampleRate, int newSamplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>& /*buffer*/,
                      MidiBuffer& /*midiMessages*/) override;
    void parameterChanged(const String& parameter, float newValue) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    tobanteAudio::EqualizerProcessor& getEQ() { return equalizerProcessor; }
    AudioProcessorValueTreeState& getPluginState() { return state; }
    UndoManager& getUndoManager() { return undo; }
    tobanteAudio::ModulationSourceProcessor modSource;
    FFAU::LevelMeterSource* getMeterSource() { return &meterSource; }

private:
    tobanteAudio::EqualizerProcessor equalizerProcessor;
    AudioBuffer<float> modBuffer;

    dsp::Gain<float> outputGain;
    double sampleRate = 0;

    tobanteAudio::GainTextConverter gainTextConverter;
    tobanteAudio::FrequencyTextConverter freqTextConverter;

    FFAU::LevelMeterSource meterSource;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModEQProcessor)
};
