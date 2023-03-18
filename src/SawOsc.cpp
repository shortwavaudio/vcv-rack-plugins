#include "SawOsc.hpp"

void SawOsc::process(const ProcessArgs &args)
{
  float freq = inputs[CV_INPUT].active
    ? rescale(inputs[CV_INPUT].getVoltage(), -10.f, 10.f, 0.00001f, .5f)
    : params[FREQ_PARAM].getValue();

  float signal = Sawcore_process(processor, dsp::FREQ_C4 / 1000.f, 0.f);

  outputs[AUDIO_OUTPUT].setVoltage(signal * 5.f);
}

Model *modelSawOsc = createModel<SawOsc, SawOscWidget>("SawOsc");
