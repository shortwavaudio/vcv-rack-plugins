#pragma once

#include "plugin.hpp"
#include "helpers/heartbeatMessage.hpp"

const int HEARTBREAKER_NUM_OUTPUTS = 5;

struct Heartbreaker : Module
{
  enum ParamIds
  {
    ENUMS(DIV_PARAM, HEARTBREAKER_NUM_OUTPUTS),
    ENUMS(MULT_PARAM, HEARTBREAKER_NUM_OUTPUTS),
    NUM_PARAMS
  };

  enum InputIds
  {
    // SYNC_INPUT,
    NUM_INPUTS
  };

  enum OutputIds
  {
    ENUMS(DIV_TRIGGER_OUTPUT, HEARTBREAKER_NUM_OUTPUTS),
    ENUMS(MULT_TRIGGER_OUTPUT, HEARTBREAKER_NUM_OUTPUTS),
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Heartbreaker() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    for(int i = 0; i < HEARTBREAKER_NUM_OUTPUTS; ++i) {
      configParam(DIV_PARAM + i, 1.f, 64.f, 1.f, "Divider");
      configParam(MULT_PARAM + i, 1.f, 64.f, 1.f, "Multiplier");

      paramQuantities[DIV_PARAM + i]->snapEnabled = true;
      paramQuantities[MULT_PARAM + i]->snapEnabled = true;

      configOutput(DIV_TRIGGER_OUTPUT + i, "Divider");
      configOutput(MULT_TRIGGER_OUTPUT + i, "Multiplier");
    }
      
    leftExpander.producerMessage = leftMessages[0];
		leftExpander.consumerMessage = leftMessages[1];	
  }

  void process(const ProcessArgs &args) override;

  heartbeatMessage leftMessages[2][3];

  bool masterActive = false;
  float masterFrequency = .5f;
  float masterPhase = 0.f;
};

struct HeartbreakerWidget : ModuleWidget
{
  HeartbreakerWidget(Heartbreaker *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/6HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    for(int i = 0; i < HEARTBREAKER_NUM_OUTPUTS; ++i) {
      addParam(createParam<RoundSmallBlackKnob>(Vec(11.f, 20.f + (60.f * i)), module, Heartbreaker::DIV_PARAM + i));
      addParam(createParam<RoundSmallBlackKnob>(Vec(56.f, 20.f + (60.f * i)), module, Heartbreaker::MULT_PARAM + i));
      addOutput(createOutput<PJ301MPort>(Vec(10.f, 50.f + (60.f * i)), module, Heartbreaker::DIV_TRIGGER_OUTPUT + i));
      addOutput(createOutput<PJ301MPort>(Vec(55.f, 50.f + (60.f * i)), module, Heartbreaker::MULT_TRIGGER_OUTPUT + i));
    }
  }
};
