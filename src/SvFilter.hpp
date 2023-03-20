#pragma once

#include "plugin.hpp"
#include "svf.h"

struct SvFilter : Module
{
  enum ParamIds
  {
    FREQ_PARAM,
    MODE_PARAM,
    Q_PARAM,
    NUM_PARAMS
  };

  enum InputIds
  {
    CV_INPUT,
    FREQ_INPUT,
    Q_INPUT,
    NUM_INPUTS
  };

  enum OutputIds
  {
    CV_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  SvFilter() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    configParam(FREQ_PARAM, 0.f, .5f, .25f, "frequency");
    configParam(MODE_PARAM, 0.f, 3.f, 0.f, "mode");
    configParam(Q_PARAM, 0.f, .5f, .25f, "q");

    Svf_process_init(processor);
  }

  void process(const ProcessArgs &args) override;

  Svf_process_type processor;
};

struct SvFilterWidget : ModuleWidget
{
  SvFilterWidget(SvFilter *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addInput(createInput<PJ301MPort>(Vec(10.f, 20.f), module, SvFilter::CV_INPUT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 100.f), module, SvFilter::MODE_PARAM));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 170.f), module, SvFilter::FREQ_PARAM));
    addInput(createInput<PJ301MPort>(Vec(10.f, 200.f), module, SvFilter::FREQ_INPUT));
    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 230.f), module, SvFilter::Q_PARAM));
    addInput(createInput<PJ301MPort>(Vec(10.f, 260.f), module, SvFilter::Q_INPUT));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, SvFilter::CV_OUTPUT));
  }
};
