#include "Test.hpp"

void Test::process(const ProcessArgs &args)
{
    float freq = params[FREQ_PARAM].getValue();
    outputs[AUDIO_OUTPUT].setVoltage(Sine_process(osc, freq, 0.f) * 5.f);
}

Model *modelTest = createModel<Test, TestWidget>("Test");
