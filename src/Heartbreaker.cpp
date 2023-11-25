#include "Heartbreaker.hpp"

void Heartbreaker::process(const ProcessArgs &args)
{
  if (leftExpander.module) {
    if (leftExpander.module->model == modelHeartbeat) {
        
      heartbeatMessage *messagesFromModule = (heartbeatMessage *)(leftExpander.consumerMessage);

      masterActive = messagesFromModule->active;
      masterFrequency = messagesFromModule->frequency;
      masterPhase = messagesFromModule->phase;
    }
	}

  for(int i = 0; i < HEARTBREAKER_NUM_OUTPUTS; ++i) {
    if(!synced) {
      synced = !!(masterPhase == 0);
    }

    if(synced) {
      multTimers[i].process(args.sampleTime * roundf(params[MULT_PARAM + i].getValue()));
      if(multTimers[i].getTime() > masterFrequency) {
        multTimers[i].reset();
      }
    }

    outputs[DIV_TRIGGER_OUTPUT + i].setVoltage(params[DIV_PARAM + i].getValue());
    outputs[MULT_TRIGGER_OUTPUT + i].setVoltage(multTimers[i].getTime() * (10.f / masterFrequency));
  }
}

Model *modelHeartbreaker = createModel<Heartbreaker, HeartbreakerWidget>("Heartbreaker");
