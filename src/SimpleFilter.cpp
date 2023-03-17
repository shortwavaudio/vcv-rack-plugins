#include "SimpleFilter.hpp"

void SimpleFilter::process(const ProcessArgs &args)
{
  float signal = inputs[CV_INPUT].getVoltage();
  float freq = params[FREQ_PARAM].getValue();

  filter.setCutoffFreq(freq);
  filter.process(signal);

  outputs[LP_OUTPUT].setVoltage(filter.lowpass());
}

Model *modelSimpleFilter = createModel<SimpleFilter, SimpleFilterWidget>("SimpleFilter");
