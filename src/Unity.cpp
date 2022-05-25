#include "Unity.hpp"

void Unity::process(const ProcessArgs &args)
{
    if( tickProcessor.process( ( inputs[CLOCK_IN].getVoltage() ) ) )
    {
        tick.trigger(0.0025f);
    }

    outputs[CLOCK_OUT].setVoltage(tick.process(args.sampleTime) * 10.f);
}

Model *modelUnity = createModel<Unity, UnityWidget>("Unity");
