#pragma once

#include "plugin.hpp"
#include "engine.h"

struct Test : Module
{
  enum ParamIds
  {
    FREQ_PARAM,
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

  Sine_process_type osc;

  float phase = 0;

  Test() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    configParam(Test::FREQ_PARAM, 0.f, 1.0, 0.1f, "Frequency");
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


    addParam(createParam<Rogan1PWhite>(Vec(7.f, 60.f), module, Test::FREQ_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 300.f), module, Test::AUDIO_OUTPUT));
  }
};
