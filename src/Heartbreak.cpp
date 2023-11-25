#include "Heartbreak.hpp"

float Heartbreak::getPhase()
{
  return timer.getTime() * (10.f / frequency);
}

bool Heartbreak::hasPeaked()
{
  return timer.getTime() > frequency;
}

void Heartbreak::incrementTimer(float deltaTime)
{
  timer.process(deltaTime);
}

bool Heartbreak::processPulse(float deltaTime)
{
  return clockPulse.process(deltaTime);
}

void Heartbreak::resetPulse()
{
  clockPulse.reset();
}

void Heartbreak::resetTimer()
{
  timer.reset();
}

void Heartbreak::setBpm(float bpmValue)
{
  bpm = roundf(bpmValue);
}

void Heartbreak::setFrequency()
{
  frequency = clockUtils.bpmToFreq(bpm);
}

void Heartbreak::triggerPulse()
{
  clockPulse.trigger();
}

void Heartbreak::process(const ProcessArgs &args)
{
  isActive = !!params[PLAY_PARAM].getValue();
  isReset = resetTrigger.process(params[RESET_PARAM].getValue());

  if(params[BPM_PARAM].getValue() != bpm) {
    setBpm(params[BPM_PARAM].getValue());
    setFrequency();
  }

  if(isActive) {
    incrementTimer(args.sampleTime);
  }

  if(playTrigger.process(params[PLAY_PARAM].getValue()) || isReset) {
    resetTimer();
    resetPulse();
  }

  if(isReset) {
    resetLightPulse.trigger(1e-1f);
  }
  
  if(hasPeaked()) {
    resetTimer();
    triggerPulse();
  }

  outputs[PHASE_OUTPUT].setVoltage(isActive ? getPhase(): 0.f);
  outputs[TRIGGER_OUTPUT].setVoltage(isActive ? processPulse(args.sampleTime) ? 10.f : 0.f : 0.f);
  lights[PLAY_LIGHT].setBrightnessSmooth(isActive ? 10.f: 0.f, args.sampleTime);

  if(resetLightPulse.process(args.sampleTime)) {
    lights[RESET_LIGHT].setBrightnessSmooth(10.f, args.sampleTime);
    outputs[RESET_OUTPUT].setVoltage(10.f);
  } else {
    lights[RESET_LIGHT].setBrightnessSmooth(0.f, args.sampleTime);
    outputs[RESET_OUTPUT].setVoltage(0.f);
  }
}

void Heartbreak::onSampleRateChange(const SampleRateChangeEvent& e)
{
  resetTimer();
  resetPulse();

  outputs[PHASE_OUTPUT].setVoltage(0.f);
  outputs[TRIGGER_OUTPUT].setVoltage(0.f);
  lights[PLAY_LIGHT].setBrightnessSmooth(isActive ? 10.f: 0.f, e.sampleTime);
}

Model *modelHeartbreak = createModel<Heartbreak, HeartbreakWidget>("Heartbreak");
