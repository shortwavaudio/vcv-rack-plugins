#include "QuadVco.hpp"

void QuadVco::process(const ProcessArgs &args)
{
  float in = inputs[CV_INPUT].getVoltage();
  // float pwm = params[PWM_PARAM].getValue();
  float freq = VCO.cvToFreq(in);

  outputs[SINE_OUTPUT].setVoltage(VCO.sine(phase) * 5.f);

  phase += VCO.deltaPhase(freq, args.sampleTime);

  if (phase >= 1.f)
  {
    phase -= 1.f;
  }
}

Model *modelQuadVco = createModel<QuadVco, QuadVcoWidget>("QuadVco");
