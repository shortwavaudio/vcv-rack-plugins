#pragma once

#include "rack.hpp"
using namespace rack;

namespace ShortwavAudio
{
  namespace utils
  {
    float bpmToFreq(float bpm)
    {
      return 60.f / bpm;
    }
  }
}
