#include "Heartbreaker.hpp"

void Heartbreaker::process(const ProcessArgs &args)
{
  if (leftExpander.module) {
    if (leftExpander.module->model == modelHeartbeat) {
        
      heartbeatMessage *messagesFromModule = (heartbeatMessage *)(leftExpander.consumerMessage);

      masterPhase = messagesFromModule->phase;
      masterFrequency = messagesFromModule->frequency;
    }
	}
}

Model *modelHeartbreaker = createModel<Heartbreaker, HeartbreakerWidget>("Heartbreaker");
