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

#include "info_view.h"

namespace tobanteAudio
{
InfoView::InfoView() {}

void InfoView::paint(Graphics& g)
{
    // Version footer
    const String version = JucePlugin_VersionString;
    g.setColour(Colours::black);
    g.setFont(32.0f);
    g.drawText("Version: " + version, getLocalBounds(), Justification::centred,
               true);
}

void InfoView::resized() {}

}  // namespace tobanteAudio