#pragma once

#include "plugin.hpp"

struct Heartbeat : Module
{
  enum ParamIds
  {
    BPM_PARAM,
    PLAY_PARAM,
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
    PLAY_LIGHT,
    NUM_LIGHTS
  };

  Heartbeat() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    configParam(BPM_PARAM, 0.f, 240.f, bpm, "BPM", "bpm");
    paramQuantities[BPM_PARAM]->snapEnabled = true;
    configParam(PLAY_PARAM, 0.f, 1.f, 0.f, "ON/OFF");

    configOutput(PHASE_OUTPUT, "Phase");
    configOutput(TRIGGER_OUTPUT, "Clock");
  }

  void process(const ProcessArgs &args) override;
  void onSampleRateChange(const SampleRateChangeEvent& e) override;

  float bpm = 120.f;
  float frequency = 0.5f;
  bool isActive = false;

  dsp::SchmittTrigger playTrigger;
  dsp::PulseGenerator pulse;
  dsp::Timer timer;

  float getPhase();
  bool hasPeaked();
  void incrementTimer(float deltaTime);
  bool processPulse(float deltaTime);
  void resetPulse();
  void resetTimer();
  void setBpm(float bpmValue);
  void setFrequency();
  void triggerPulse();
};

struct HeartbeatWidget : ModuleWidget
{
  HeartbeatWidget(Heartbeat *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/3HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createLightParam<VCVLightLatch<MediumSimpleLight<GreenLight>>>(Vec(13.f, 20.f), module, Heartbeat::PLAY_PARAM, Heartbeat::PLAY_LIGHT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(11.f, 50.f), module, Heartbeat::BPM_PARAM));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 280.f), module, Heartbeat::PHASE_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(10.f, 310.f), module, Heartbeat::TRIGGER_OUTPUT));
  }
};
