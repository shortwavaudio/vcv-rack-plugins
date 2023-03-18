#pragma once

#include "plugin.hpp"
#include "tricore.h"

struct TriOsc : Module
{
  enum ParamIds
  {
    FREQ_PARAM,
    NUM_PARAMS
  };

  enum InputIds
  {
    CV_INPUT,
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

  TriOsc() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(FREQ_PARAM, .00001f, .5f, .1f);

    Tricore_process_init(processor);
  }

  void process(const ProcessArgs &args) override;

  Tricore_process_type processor;
};

struct TriOscWidget : ModuleWidget
{
  TriOscWidget(TriOsc *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(10.f, 20.f), module, TriOsc::CV_INPUT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 170.f), module, TriOsc::FREQ_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, TriOsc::AUDIO_OUTPUT));
  }
};
