#pragma once

#include "plugin.hpp"
#include "helpers/heartbeatMessage.hpp"

const int HEARTBREAKER_NUM_OUTPUTS = 5;

struct Heartbreaker : Module
{
  enum ParamIds
  {
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
    ENUMS(TRIGGER_OUTPUT, HEARTBREAKER_NUM_OUTPUTS),
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Heartbreaker() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    for(int i = 0; i < HEARTBREAKER_NUM_OUTPUTS; ++i) {
      configParam(MULT_PARAM + i, -64.f, 64.f, 0.f, "Multiplier");
      paramQuantities[MULT_PARAM + i]->snapEnabled = true;
    }
      
    leftExpander.producerMessage = leftMessages[0];
		leftExpander.consumerMessage = leftMessages[1];	
  }

  void process(const ProcessArgs &args) override;

  heartbeatMessage leftMessages[2][2];

  float masterPhase = 0.f;
  float masterFrequency = .5f;
};

struct HeartbreakerWidget : ModuleWidget
{
  HeartbreakerWidget(Heartbreaker *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    for(int i = 0; i < HEARTBREAKER_NUM_OUTPUTS; ++i) {
      addParam(createParam<RoundSmallBlackKnob>(Vec(11.f, 20.f + (60.f * i)), module, Heartbreaker::MULT_PARAM + i));
      addOutput(createOutput<PJ301MPort>(Vec(10.f, 50.f + (60.f * i)), module, Heartbreaker::TRIGGER_OUTPUT + i));
    }
  }
};
