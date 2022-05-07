#include "Test.hpp"

void Test::process(const ProcessArgs &args)
{
    outputs[AUDIO_OUTPUT].setVoltage(random::uniform() * 5.0f);
}

Model *modelTest = createModel<Test, TestWidget>("Test");
