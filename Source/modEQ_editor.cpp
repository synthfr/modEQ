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

#include "modEQ_editor.h"
#include "modEQ_processor.h"
#include "parameters/parameters.h"

ModEQEditor::ModEQEditor(ModEQProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
    , menuController(processor, menuButtons)
    , output(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox)
{
    // Global look & feel
    setLookAndFeel(&tobanteLookAndFeel);

    // Social buttons
    addAndMakeVisible(socialButtons);

    // Menu
    addAndMakeVisible(menuButtons);
    // Connect buttons
    menuController.toggleBypass   = [this]() { DBG("BYPASS"); };
    menuController.toggleSettings = [this]() {
        infoView.setVisible(false);
        settingsView.setVisible(!settingsView.isVisible());
        analyserView->setVisible(!settingsView.isVisible());
        meter->setVisible(!settingsView.isVisible());
    };
    menuController.toggleInfo = [this]() {
        settingsView.setVisible(false);
        infoView.setVisible(!infoView.isVisible());
        analyserView->setVisible(!infoView.isVisible());
        meter->setVisible(!infoView.isVisible());
    };

    // Settings & Info
    addAndMakeVisible(infoView);
    addAndMakeVisible(settingsView);
    infoView.setVisible(false);
    settingsView.setVisible(false);

    // Modulation
    for (int i = 1; i < 2; ++i)
    {
        using MSC = tobanteAudio::ModulationSourceController;
        using MSV = tobanteAudio::ModulationSourceView;

        auto* const modView = modViews.add(new MSV(i));
        modController.add(new MSC(i, processor, processor.modSource, *modView));

        addAndMakeVisible(modView);
    }

    // EQ bands
    for (int i = 0; i < processor.getEQ().getNumBands(); ++i)
    {
        using BC = tobanteAudio::BandController;
        using BV = tobanteAudio::BandView;

        const auto color     = processor.getEQ().getBand(i)->colour;
        auto* const bandView = bandViews.add(new BV(i, color));
        bandControllers.add(new BC(i, processor, processor.getEQ(), *bandView));

        addAndMakeVisible(bandView);
    }

    // Meter
    lnf = new tobanteAudio::TobanteMetersLookAndFeel();
    lnf->setColour(FFAU::LevelMeter::lmMeterGradientLowColour, tobanteAudio::ORANGE);

    meter = new FFAU::LevelMeter();
    meter->setMeterFlags(FFAU::LevelMeter::MaxNumber);
    meter->setLookAndFeel(lnf);
    meter->setMeterSource(processor.getMeterSource());
    addAndMakeVisible(meter);

    // Plot
    using AC = tobanteAudio::AnalyserController;
    using AV = tobanteAudio::AnalyserView;

    auto& eq           = processor.getEQ();
    analyserView       = std::make_unique<AV>();
    analyserController = std::make_unique<AC>(eq, bandControllers, *analyserView.get());
    addAndMakeVisible(analyserView.get());

    // Master Section
    addAndMakeVisible(output);
    output.setTooltip(translate("Overall Gain"));
    output.setName("Master");

    using SliderAttachment  = AudioProcessorValueTreeState::SliderAttachment;
    auto& state             = processor.getPluginState();
    const auto output_param = tobanteAudio::Parameters::Output;
    attachments.add(new SliderAttachment(state, output_param, output));

    // Window settings
    setResizable(true, true);
    setResizeLimits(1000, 750, 2990, 1800);
    setSize(1000, 750);
    tooltipWindow->setMillisecondsBeforeTipAppears(1000);

#ifdef JUCE_OPENGL
    openGLContext.attachTo(*getTopLevelComponent());
#endif
}

ModEQEditor::~ModEQEditor()
{
    setLookAndFeel(nullptr);
    PopupMenu::dismissAllActiveMenus();

#ifdef JUCE_OPENGL
    openGLContext.detach();
#endif
}

void ModEQEditor::paint(Graphics& g)
{
    // Background
    const auto backgroundColour
        = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    g.fillAll(backgroundColour);

    // Frame for master slider
    const auto color = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    g.setColour(color.brighter().withAlpha(0.5f));
    g.fillRect(outputSliderFrame);
}

void ModEQEditor::resized()
{
    auto area = getLocalBounds();

    // Facebook & Gitub
    const auto button_height = static_cast<int>(area.getHeight() / 20);
    socialButtons.setBounds(area.removeFromBottom(button_height));
    menuButtons.setBounds(area.removeFromTop(button_height));

    // EQ Bands
    auto band_space  = area.removeFromBottom((getHeight() / 10) * 4);
    auto const width = roundToInt(band_space.getWidth()) / (bandViews.size() + 1);
    for (auto* bandView : bandViews)
    {
        bandView->setBounds(band_space.removeFromLeft(width));
    }

    // Master output
    outputSliderFrame
        = band_space.removeFromBottom(band_space.getHeight() / 2).reduced(5);
    output.setBounds(outputSliderFrame.reduced(8));

    // Meter
    auto meter_area = area;
    meter->setBounds(meter_area.removeFromRight(area.getWidth() / 12));

    // FFT
    analyserView->setBounds(area);

    // Settings & Info
    infoView.setBounds(area);
    settingsView.setBounds(area);
}
