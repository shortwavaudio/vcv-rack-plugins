#include "SimpleFilter.hpp"

void SimpleFilter::process(const ProcessArgs &args)
{
  float signal = inputs[CV_INPUT].getVoltage();
  float freq = params[FREQ_PARAM].getValue();

  outputs[HP_OUTPUT].setVoltage(signal);
  outputs[LP_OUTPUT].setVoltage(freq);
}

Model *modelSimpleFilter = createModel<SimpleFilter, SimpleFilterWidget>("SimpleFilter");
