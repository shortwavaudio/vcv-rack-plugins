#pragma once

#include "plugin.hpp"
#include "adsr.h"

struct Envelope : Module
{
  enum ParamIds
  {
    A_PARAM,
    D_PARAM,
    S_PARAM,
    R_PARAM,
    NUM_PARAMS
  };

  enum InputIds
  {
    GATE_INPUT,
    NUM_INPUTS
  };

  enum OutputIds
  {
    ENV_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Envelope() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    configParam(A_PARAM, 0.f, 1.f, 0.f);
    configParam(D_PARAM, 0.f, 1.f, .5f);
    configParam(S_PARAM, 0.f, 1.f, 1.f);
    configParam(R_PARAM, 0.f, 1.f, .5f);

    Adsr_process_init(processor);
  }

  void process(const ProcessArgs &args) override;

  Adsr_process_type processor;
};

struct EnvelopeWidget : ModuleWidget
{
  EnvelopeWidget(Envelope *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(10.f, 20.f), module, Envelope::GATE_INPUT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 100.f), module, Envelope::A_PARAM));
    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 130.f), module, Envelope::D_PARAM));
    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 160.f), module, Envelope::S_PARAM));
    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 190.f), module, Envelope::R_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, Envelope::ENV_OUTPUT));
  }
};
