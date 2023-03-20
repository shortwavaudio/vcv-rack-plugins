#include "SvFilter.hpp"

void SvFilter::process(const ProcessArgs &args)
{
  float signal = inputs[CV_INPUT].getVoltage();
  float q = inputs[Q_INPUT].active
    ? rescale(inputs[Q_INPUT].getVoltage(), -5.f, 5.f, 0.f, .5f)
    : params[Q_PARAM].getValue();
  float freq = inputs[FREQ_INPUT].active
    ? rescale(inputs[FREQ_INPUT].getVoltage(), -5.f, 5.f, 0.f, .5f)
    : params[FREQ_PARAM].getValue();
  int mode = (int)(params[MODE_PARAM].getValue());

  float processed = Svf_process(processor, signal, freq, q, mode);

  outputs[CV_OUTPUT].setVoltage(processed);
}

Model *modelSvFilter = createModel<SvFilter, SvFilterWidget>("SvFilter");
