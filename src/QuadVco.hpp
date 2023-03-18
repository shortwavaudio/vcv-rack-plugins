#pragma once

#include "plugin.hpp"
#include "helpers/oscillators.hpp"

struct QuadVco : Module
{
  enum ParamIds
  {
    PWM_PARAM,
    NUM_PARAMS
  };

  enum InputIds
  {
    CV_INPUT,
    NUM_INPUTS
  };

  enum OutputIds
  {
    SAW_OUTPUT,
    SINE_OUTPUT,
    SQUARE_OUTPUT,
    TRIANGLE_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  QuadVco() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(PWM_PARAM, .1f, .9f, .5f);
    phase = 0.f;
  }

  void process(const ProcessArgs &args) override;

  Oscillator VCO;
  float phase;
};

struct QuadVcoWidget : ModuleWidget
{
  QuadVcoWidget(QuadVco *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/6HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(10.f, 20.f), module, QuadVco::CV_INPUT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 170.f), module, QuadVco::PWM_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(15.f, 280.f), module, QuadVco::SINE_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(45.f, 280.f), module, QuadVco::SQUARE_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(15.f, 310.f), module, QuadVco::SAW_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(45.f, 310.f), module, QuadVco::TRIANGLE_OUTPUT));
  }
};
