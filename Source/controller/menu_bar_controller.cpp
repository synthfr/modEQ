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

#include "menu_bar_controller.h"

namespace tobanteAudio
{
MenuBarController::MenuBarController(ModEQProcessor& p, tobanteAudio::MenuBarView& v)
    : processor(p), view(v)
{
    view.undoButton.addListener(this);
    view.redoButton.addListener(this);
    view.powerButton.addListener(this);
    view.settingButton.addListener(this);
    view.infoButton.addListener(this);
}
void MenuBarController::buttonClicked(Button* b)
{
    if (b == &view.undoButton)
    {
        processor.getUndoManager().undo();
    }

    if (b == &view.redoButton)
    {
        processor.getUndoManager().redo();
    }

    if (b == &view.powerButton)
    {
        toggleBypass();
    }

    if (b == &view.settingButton)
    {
        toggleSettings();
    }

    if (b == &view.infoButton)
    {
        toggleInfo();
    }
}
}  // namespace tobanteAudio