#pragma once

#include "plugin.hpp"

struct Test : Module
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
    AUDIO_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Test() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  void process(const ProcessArgs &args) override;
};

struct TestWidget : ModuleWidget
{
  TestWidget(Test *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/vcv_demo.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 300.f), module, Test::AUDIO_OUTPUT));
  }
};
