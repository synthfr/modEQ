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
#include "../modEQ_processor.h"
#include "../view/menu_bar_view.h"

namespace tobanteAudio
{
/**
 * @brief Controller for the MenuBarView component.
 */
class MenuBarController : public Button::Listener
{
public:
    /**
     * @brief Constructor.
     */
    MenuBarController(ModEQProcessor&, tobanteAudio::MenuBarView& /*v*/);

    /**
     * @brief Listens for button clicks from view. Dispatches function pointers.
     */
    void buttonClicked(Button* b) override;

    /**
     * @brief Called when the bypass button was pressed.
     */
    std::function<void()> toggleBypass;

    /**
     * @brief Called when the settings button was pressed.
     */
    std::function<void()> toggleSettings;

    /**
     * @brief Called when the info button was pressed.
     */
    std::function<void()> toggleInfo;

private:
    ModEQProcessor& processor;
    tobanteAudio::MenuBarView& view;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuBarController)
};
}  // namespace tobanteAudio