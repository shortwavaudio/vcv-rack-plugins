#include "SawOsc.hpp"

void SawOsc::process(const ProcessArgs &args)
{

  float freq = params[FREQ_PARAM].getValue();
  float signal = Sawcore_process(processor, freq, 0.f);
  outputs[AUDIO_OUTPUT].setVoltage(signal * 5.f);
}

Model *modelSawOsc = createModel<SawOsc, SawOscWidget>("SawOsc");
