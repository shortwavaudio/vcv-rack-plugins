#include "Tempo.hpp"

void Tempo::process(const ProcessArgs &args)
{
  timer.process(args.sampleTime);

  if(timer.getTime() > 1.f) {
    timer.reset();
  }

  outputs[TRIGGER_OUTPUT].setVoltage(timer.getTime());
}

Model *modelTempo = createModel<Tempo, TempoWidget>("Tempo");
