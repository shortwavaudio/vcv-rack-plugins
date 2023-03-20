#include "Envelope.hpp"

void Envelope::process(const ProcessArgs &args)
{
  float gate = inputs[GATE_INPUT].getVoltage();
  float attack = params[A_PARAM].getValue();
  float decay = params[D_PARAM].getValue();
  float sustain = params[S_PARAM].getValue();
  float release = params[R_PARAM].getValue();

  processor.knob1 = attack;
  processor.knob2 = decay;
  processor.knob3 = release;
  processor.knob4 = sustain;

  outputs[ENV_OUTPUT].setVoltage(
    Adsr_process(processor, gate)
  );
}

Model *modelEnvelope = createModel<Envelope, EnvelopeWidget>("Envelope");
