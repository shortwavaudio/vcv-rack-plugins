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

void Heartbeat::resetTimer()
{
  timer.reset();
}

void Heartbeat::setBpm(float bpmValue)
{
  bpm = bpmValue;
}

void Heartbeat::setFrequency()
{
  frequency = 60.f / bpm;
}

void Heartbeat::process(const ProcessArgs &args)
{
  if(params[BPM_PARAM].getValue() != bpm) {
    setBpm(params[BPM_PARAM].getValue());
    setFrequency();
  }

  incrementTimer(args.sampleTime);

  if(hasPeaked()) {
    resetTimer();
    pulse.trigger();
  }

  outputs[PHASE_OUTPUT].setVoltage(getPhase());
  outputs[TRIGGER_OUTPUT].setVoltage(pulse.process(args.sampleTime) ? 10.f : 0.f);
}

Model *modelHeartbeat = createModel<Heartbeat, HeartbeatWidget>("Heartbeat");
