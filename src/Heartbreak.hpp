#pragma once

#include "plugin.hpp"
#include "helpers/utils.hpp"

struct Heartbreak : Module
{
  enum ParamIds
  {
    BPM_PARAM,
    PLAY_PARAM,
    RESET_PARAM,
    NUM_PARAMS
  };

  enum InputIds
  {
    NUM_INPUTS
  };

  enum OutputIds
  {
    PHASE_OUTPUT,
    RESET_OUTPUT,
    TRIGGER_OUTPUT,
    NUM_OUTPUTS
  };

  enum LightIds
  {
    PLAY_LIGHT,
    RESET_LIGHT,
    NUM_LIGHTS
  };

  Heartbreak() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

    configParam(BPM_PARAM, 0.f, 240.f, bpm, "BPM", "bpm");
    paramQuantities[BPM_PARAM]->snapEnabled = true;
    configParam(PLAY_PARAM, 0.f, 1.f, 0.f, "ON/OFF");
    configParam(RESET_PARAM, 0.f, 1.f, 0.f, "Reset");

    configOutput(PHASE_OUTPUT, "Phase");
    configOutput(RESET_OUTPUT, "Reset");
    configOutput(TRIGGER_OUTPUT, "Clock");
  }

  void process(const ProcessArgs &args) override;
  void onSampleRateChange(const SampleRateChangeEvent& e) override;

  float bpm = 120.f;
  float frequency = 0.5f;
  bool isActive = false;
  bool isReset = false;

  dsp::SchmittTrigger playTrigger, resetTrigger;
  dsp::PulseGenerator clockPulse, resetLightPulse;
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

  ShortwavAudio::utils::clock clockUtils;
};

struct HeartbreakWidget : ModuleWidget
{
  HeartbreakWidget(Heartbreak *module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/15HP.svg")));

    addChild(createWidget<ScrewSilver>(Vec(0, 0)));
    addChild(createWidget<ScrewSilver>(Vec(box.size.x - 1 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    addParam(createLightParam<VCVLightLatch<MediumSimpleLight<GreenLight>>>(Vec(13.f, 20.f), module, Heartbreak::PLAY_PARAM, Heartbreak::PLAY_LIGHT));

    addParam(createParam<RoundSmallBlackKnob>(Vec(11.f, 50.f), module, Heartbreak::BPM_PARAM));

    addParam(createLightParam<VCVLightButton<MediumSimpleLight<RedLight>>>(Vec(13.f, 100.f), module, Heartbreak::RESET_PARAM, Heartbreak::RESET_LIGHT));

    addOutput(createOutput<PJ301MPort>(Vec(10.f, 230.f), module, Heartbreak::RESET_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(10.f, 260.f), module, Heartbreak::PHASE_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(10.f, 290.f), module, Heartbreak::TRIGGER_OUTPUT));
  }
};
