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
#include "../../JuceLibraryCode/JuceHeader.h"

// tobanteAudio
#include "../settings/constants.h"

namespace tobanteAudio
{
/**
 * @brief Component for the spectrum analyser.
 */
class AnalyserView : public Component, public ChangeBroadcaster
{
public:
    /**
     * @brief Model for a band handle (graber, click point).
     */
    struct BandHandle
    {
        int id{};
        float x{};
        float y{};
        float label_x{};
        float label_y{};
        Colour color{Colours::white};
    };

    /**
     * @brief Constructor.
     */
    AnalyserView() = default;

    /**
     * @brief Default destructor.
     */
    ~AnalyserView() override = default;

    /**
     * @brief Paint in the component. Called by JUCE.
     */
    void paint(Graphics& /*g*/) override;

    /**
     * @brief Resize & position child components. Called by JUCE.
     */
    void resized() override;

    Rectangle<int> plotFrame;
    Path frequencyResponse;
    Path in_analyser;
    Path out_analyser;

    PopupMenu contextMenu;

    std::vector<BandHandle> handles;

    inline static float get_position_for_frequency(float freq) noexcept
    {
        return (std::log(freq / 20.0f) / std::log(2.0f)) / 10.0f;
    }
    inline static float get_frequency_for_position(float pos) noexcept
    {
        return 20.0f * std::pow(2.0f, pos * 10.0f);
    }
    inline static float get_position_for_gain(float gain, float top,
                                              float bottom) noexcept
    {
        return jmap(Decibels::gainToDecibels(gain, -MAX_DB), -MAX_DB, MAX_DB, bottom,
                    top);
    }
    inline static float get_gain_for_position(float pos, float top, float bottom) noexcept
    {
        return Decibels::decibelsToGain(jmap(pos, bottom, top, -MAX_DB, MAX_DB), -MAX_DB);
    }

    /**
     * @brief Checks if two positions are in a given radius.
     */
    inline static bool overlap_with_radius(float obj_pos, float mouse_pos,
                                           int radius) noexcept
    {
        return std::abs(obj_pos - mouse_pos) < radius;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalyserView)
};

}  // namespace tobanteAudio
