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
}

Model *modelHeartbreaker = createModel<Heartbreaker, HeartbreakerWidget>("Heartbreaker");
