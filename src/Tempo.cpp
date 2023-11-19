#include "Tempo.hpp"

float Tempo::getPhase()
{
  return timer.getTime() * (10.f / frequency);
}

bool Tempo::hasPeaked()
{
  return timer.getTime() > frequency;
}

void Tempo::incrementTimer(float deltaTime)
{
  timer.process(deltaTime);
}

void Tempo::resetTimer()
{
  timer.reset();
}

void Tempo::setBpm(float bpmValue)
{
  bpm = bpmValue;
}

void Tempo::setFrequency()
{
  frequency = 60.f / bpm;
}

void Tempo::process(const ProcessArgs &args)
{
  if(params[BPM_PARAM].getValue() != bpm) {
    setBpm(params[BPM_PARAM].getValue());
    setFrequency();
  }

  incrementTimer(args.sampleTime);

  if(hasPeaked()) {
    resetTimer();
  }

  outputs[TRIGGER_OUTPUT].setVoltage(getPhase());
}

Model *modelTempo = createModel<Tempo, TempoWidget>("Tempo");
