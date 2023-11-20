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
  return pulse.process(deltaTime);
}

void Heartbeat::resetPulse()
{
  pulse.reset();
}

void Heartbeat::resetTimer()
{
  timer.reset();
}

void Heartbeat::setBpm(float bpmValue)
{
  bpm = floorf(bpmValue);
}

void Heartbeat::setFrequency()
{
  frequency = 60.f / bpm;
}

void Heartbeat::triggerPulse()
{
  pulse.trigger();
}

void Heartbeat::process(const ProcessArgs &args)
{
  isActive = !!params[PLAY_PARAM].getValue();

  if(params[BPM_PARAM].getValue() != bpm) {
    setBpm(params[BPM_PARAM].getValue());
    setFrequency();
  }

  if(playTrigger.process(params[PLAY_PARAM].getValue())) {
    resetTimer();
    resetPulse();
  }

  if(isActive) {
    incrementTimer(args.sampleTime);
  }
  
  if(hasPeaked()) {
    resetTimer();
    triggerPulse();
  }

  outputs[PHASE_OUTPUT].setVoltage(isActive ? getPhase(): 0.f);
  outputs[TRIGGER_OUTPUT].setVoltage(isActive ? processPulse(args.sampleTime) ? 10.f : 0.f : 0.f);
  lights[PLAY_LIGHT].setBrightness(isActive ? 10.f: 0.f);
}

void Heartbeat::onSampleRateChange(const SampleRateChangeEvent& e)
{
  resetTimer();
  resetPulse();

  outputs[PHASE_OUTPUT].setVoltage(0.f);
  outputs[TRIGGER_OUTPUT].setVoltage(0.f);
  lights[PLAY_LIGHT].setBrightness(isActive ? 10.f: 0.f);
}

Model *modelHeartbeat = createModel<Heartbeat, HeartbeatWidget>("Heartbeat");
