#pragma once

#include "plugin.hpp"

struct Tempo : Module
{
  enum ParamIds
  {
    NUM_PARAMS
  };

  enum InputIds
  {
    NUM_INPUTS
  };

  enum OutputIds
  {
    TRIGGER_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Tempo() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  void process(const ProcessArgs &args) override;

  dsp::Timer timer;
};

struct TempoWidget : ModuleWidget
{
  TempoWidget(Tempo *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, Tempo::TRIGGER_OUTPUT));
  }
};
