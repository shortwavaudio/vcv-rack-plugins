#include "QuadVco.hpp"

void QuadVco::process(const ProcessArgs &args)
{
  float in = inputs[CV_INPUT].getVoltage();
  float pwm = inputs[PWM_INPUT].active
    ? rescale(inputs[PWM_INPUT].getVoltage(), -10.f, 10.f, .1f, .9f)
    : params[PWM_PARAM].getValue();
  float freq = VCO.cvToFreq(in);

  outputs[SAW_OUTPUT].setVoltage(VCO.sawtooth(phase, pwm) * 5.f);
  outputs[SINE_OUTPUT].setVoltage(VCO.sine(phase) * 5.f);
  outputs[SQUARE_OUTPUT].setVoltage(VCO.square(phase, pwm) * 5.f);
  outputs[TRIANGLE_OUTPUT].setVoltage(VCO.triangle(phase) * 5.f);

  outputs[MIX_OUTPUT].setVoltage((VCO.sawtooth(phase, pwm) + VCO.square(phase, pwm)) * VCO.triangle(phase) * 2.5f);

  phase += VCO.deltaPhase(freq, args.sampleTime);

  if (phase >= 1.f)
  {
    phase -= 1.f;
  }
}

Model *modelQuadVco = createModel<QuadVco, QuadVcoWidget>("QuadVco");
