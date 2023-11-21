#pragma once

#include "rack.hpp"
using namespace rack;

namespace ShortwavAudio
{
  namespace osc
  {
    float blade(float p)
    {
      return (2.f - p * 2.f) -1.f;
    };

    float phasor(float p)
    {
      return p * 2.f - 1.f;
    };

    float sawtooth(float p, float m)
    {
      return (((p < m) ? 2.f * p : 2.f + 2.f * p) - 2.f) / 2.f;
    };

    float sine(float p)
    {
      return sinf(2.f * M_PI * p);
    };

    float square(float p, float m)
    {
      return p > m ? -1.f : 1.f;
    };

    float triangle(float p)
    {
      if (p < 0.25f)
        return 4.f * p;
      else if (p < 0.75f)
        return 2.f - 4.f * p;

      return -4.f + 4.f * p;
    };

    float noise()
    {
      return random::uniform() * 2.f - 1.f;
    };

    float deltaPhase(float f, float d)
    {
      return math::clamp(f * d, 1e-6, 0.5f);
    }

    float cvToFreq(float pitch)
    {
      return dsp::FREQ_C4 * std::pow(2.f, pitch);
    }
  };
}
