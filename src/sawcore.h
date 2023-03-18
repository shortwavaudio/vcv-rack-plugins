
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef SAWCORE_H
#define SAWCORE_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "util.h"

typedef struct _tuple___bool_real__ {
   uint8_t field_0;
   float field_1;
} _tuple___bool_real__;

typedef struct Sawcore__ctx_type_0 {
   float ptr_w2_ret_1;
   uint8_t ptr_w2_ret_0;
} Sawcore__ctx_type_0;

typedef Sawcore__ctx_type_0 Sawcore_ptr_w2_type;

void Sawcore__ctx_type_0_init(Sawcore__ctx_type_0 &_output_);

static_inline void Sawcore_ptr_w2_init(Sawcore__ctx_type_0 &_output_){
   Sawcore__ctx_type_0_init(_output_);
   return ;
}

void Sawcore_ptr_w2(Sawcore__ctx_type_0 &_ctx, float phase, float rate);

typedef Sawcore__ctx_type_0 Sawcore_ptr_w2_ret_0_type;

static_inline void Sawcore_ptr_w2_ret_0_init(Sawcore__ctx_type_0 &_output_){
   Sawcore__ctx_type_0_init(_output_);
   return ;
}

static_inline uint8_t Sawcore_ptr_w2_ret_0(Sawcore__ctx_type_0 &_ctx){
   return _ctx.ptr_w2_ret_0;
};

typedef Sawcore__ctx_type_0 Sawcore_ptr_w2_ret_1_type;

static_inline void Sawcore_ptr_w2_ret_1_init(Sawcore__ctx_type_0 &_output_){
   Sawcore__ctx_type_0_init(_output_);
   return ;
}

static_inline float Sawcore_ptr_w2_ret_1(Sawcore__ctx_type_0 &_ctx){
   return _ctx.ptr_w2_ret_1;
};

typedef struct Sawcore__ctx_type_1 {
   uint8_t reset_state;
   float reset_phase;
   float rate;
   float phase;
   Sawcore__ctx_type_0 _inst622;
   Util__ctx_type_0 _inst351;
   Util__ctx_type_1 _inst13b;
} Sawcore__ctx_type_1;

typedef Sawcore__ctx_type_1 Sawcore_process_type;

void Sawcore__ctx_type_1_init(Sawcore__ctx_type_1 &_output_);

static_inline void Sawcore_process_init(Sawcore__ctx_type_1 &_output_){
   Sawcore__ctx_type_1_init(_output_);
   return ;
}

float Sawcore_process(Sawcore__ctx_type_1 &_ctx, float cv, float reset);

typedef Sawcore__ctx_type_1 Sawcore_noteOn_type;

static_inline void Sawcore_noteOn_init(Sawcore__ctx_type_1 &_output_){
   Sawcore__ctx_type_1_init(_output_);
   return ;
}

static_inline void Sawcore_noteOn(Sawcore__ctx_type_1 &_ctx, int note, int velocity, int channel){
}

typedef Sawcore__ctx_type_1 Sawcore_noteOff_type;

static_inline void Sawcore_noteOff_init(Sawcore__ctx_type_1 &_output_){
   Sawcore__ctx_type_1_init(_output_);
   return ;
}

static_inline void Sawcore_noteOff(Sawcore__ctx_type_1 &_ctx, int note, int channel){
}

typedef Sawcore__ctx_type_1 Sawcore_controlChange_type;

static_inline void Sawcore_controlChange_init(Sawcore__ctx_type_1 &_output_){
   Sawcore__ctx_type_1_init(_output_);
   return ;
}

static_inline void Sawcore_controlChange(Sawcore__ctx_type_1 &_ctx, int control, int value, int channel){
}

typedef Sawcore__ctx_type_1 Sawcore_default_type;

static_inline void Sawcore_default_init(Sawcore__ctx_type_1 &_output_){
   Sawcore__ctx_type_1_init(_output_);
   return ;
}

static_inline void Sawcore_default(Sawcore__ctx_type_1 &_ctx){
   _ctx.rate = 0.759366720147f;
};



#endif // SAWCORE_H
