
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#include "util.h"

void Util__ctx_type_3_init(Util__ctx_type_3 &_output_){
   Util__ctx_type_3 _ctx;
   _ctx.y1 = 0.0f;
   _ctx.x1 = 0.0f;
   _output_ = _ctx;
   return ;
}

float Util_dcblock(Util__ctx_type_3 &_ctx, float x0){
   float y0;
   y0 = (x0 + (- _ctx.x1) + (0.995f * _ctx.y1));
   _ctx.x1 = x0;
   _ctx.y1 = y0;
   return y0;
}


