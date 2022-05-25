#pragma once

#include "plugin.hpp"
#include "engine.h"

struct Unity : Module
{
  enum ParamIds
  {
    NUM_PARAMS
  };

  enum InputIds
  {
    CLOCK_IN,
    NUM_INPUTS
  };

  enum OutputIds
  {
    CLOCK_OUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  dsp::SchmittTrigger tickProcessor;
  dsp::PulseGenerator tick;

  Unity() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  void process(const ProcessArgs &args) override;
};

struct UnityWidget : ModuleWidget
{
  UnityWidget(Unity *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/panel_645x380.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(10, 30), module, Unity::CLOCK_IN));
    addOutput(createOutput<PJ301MPort>(Vec(10, 60), module, Unity::CLOCK_OUT));
  }
};
