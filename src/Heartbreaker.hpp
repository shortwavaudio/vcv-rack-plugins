#pragma once

#include "plugin.hpp"
#include "helpers/heartbeatMessage.hpp"

struct Heartbreaker : Module
{
  enum ParamIds
  {
    NUM_PARAMS
  };

  enum InputIds
  {
    // SYNC_INPUT,
    NUM_INPUTS
  };

  enum OutputIds
  {
    NUM_OUTPUTS
  };

  enum LightIds
  {
    NUM_LIGHTS
  };

  Heartbreaker() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    leftExpander.producerMessage = leftMessages[0];
		leftExpander.consumerMessage = leftMessages[1];	
  }

  void process(const ProcessArgs &args) override;

  heartbeatMessage leftMessages[2][2];

  float phase = 0.f;
  float frequency = .5f;
};

struct HeartbreakerWidget : ModuleWidget
{
  HeartbreakerWidget(Heartbreaker *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    // addInput(createInput<PJ301MPort>(Vec(10.f, 20.f), module, Heartbreaker::SYNC_INPUT));
  }
};
