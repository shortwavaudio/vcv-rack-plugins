#pragma once

#include "plugin.hpp"

struct SimpleFilter : Module
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
    LP_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  SimpleFilter() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(FREQ_PARAM, .0001f, .02f, .001f);
  }

  void process(const ProcessArgs &args) override;

  dsp::TRCFilter<float> filter;
};

struct SimpleFilterWidget : ModuleWidget
{
  SimpleFilterWidget(SimpleFilter *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(10.f, 20.f), module, SimpleFilter::CV_INPUT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 170.f), module, SimpleFilter::FREQ_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, SimpleFilter::LP_OUTPUT));
  }
};
