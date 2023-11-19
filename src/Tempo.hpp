#pragma once

#include "plugin.hpp"

struct Tempo : Module
{
  enum ParamIds
  {
    BPM_PARAM,
    NUM_PARAMS
  };

  enum InputIds
  {
    NUM_INPUTS
  };

  enum OutputIds
  {
    PHASE_OUTPUT,
    TRIGGER_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Tempo() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(BPM_PARAM, 0.f, 240.f, bpm);
  }

  void process(const ProcessArgs &args) override;

  float bpm = 120.f;
  float frequency = 0.5f;

  dsp::Timer timer;

  float getPhase();
  bool hasPeaked();
  void incrementTimer(float deltaTime);
  void resetTimer();

  void setBpm(float bpmValue);
  void setFrequency();
};

struct TempoWidget : ModuleWidget
{
  TempoWidget(Tempo *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createParam<RoundSmallBlackKnob>(Vec(10.f, 50.f), module, Tempo::BPM_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 280.f), module, Tempo::PHASE_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, Tempo::TRIGGER_OUTPUT));
  }
};
