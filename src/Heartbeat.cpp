#include "Heartbeat.hpp"

float Heartbeat::getPhase()
{
  return timer.getTime() * (10.f / frequency);
}

bool Heartbeat::hasPeaked()
{
  return timer.getTime() > frequency;
}

void Heartbeat::incrementTimer(float deltaTime)
{
  timer.process(deltaTime);
}

bool Heartbeat::processPulse(float deltaTime)
{
  return clockPulse.process(deltaTime);
}

void Heartbeat::resetPulse()
{
  clockPulse.reset();
}

void Heartbeat::resetTimer()
{
  timer.reset();
}

void Heartbeat::setBpm(float bpmValue)
{
  bpm = roundf(bpmValue);
}

void Heartbeat::setFrequency()
{
  frequency = ShortwavAudio::utils::bpmToFreq(bpm);
}

void Heartbeat::triggerPulse()
{
  clockPulse.trigger();
}

void Heartbeat::process(const ProcessArgs &args)
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

  if(rightExpander.module) {
    if (rightExpander.module->model == modelHeartbreaker) {
      heartbeatMessage *messageToExpander = (heartbeatMessage*)(rightExpander.module->leftExpander.producerMessage);

      messageToExpander->active = isActive;
      messageToExpander->frequency = frequency;
      messageToExpander->phase = timer.getTime();

      rightExpander.module->leftExpander.requestMessageFlip();
    }
  }
}

void Heartbeat::onSampleRateChange(const SampleRateChangeEvent& e)
{
  resetTimer();
  resetPulse();

  outputs[PHASE_OUTPUT].setVoltage(0.f);
  outputs[TRIGGER_OUTPUT].setVoltage(0.f);
  lights[PLAY_LIGHT].setBrightnessSmooth(isActive ? 10.f: 0.f, e.sampleTime);
}

Model *modelHeartbeat = createModel<Heartbeat, HeartbeatWidget>("Heartbeat");
