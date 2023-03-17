#include "SimpleFilter.hpp"

void SimpleFilter::process(const ProcessArgs &args)
{
  float signal = inputs[CV_INPUT].getVoltage();
  float freq = params[FREQ_PARAM].getValue();
  float Q = params[Q_PARAM].getValue();
  float gain = 1.f;

  bFilter.setParameters(bFilter.LOWPASS, freq / args.sampleRate, Q, gain);

  outputs[LP_OUTPUT].setVoltage(bFilter.process(signal));
}

Model *modelSimpleFilter = createModel<SimpleFilter, SimpleFilterWidget>("SimpleFilter");
