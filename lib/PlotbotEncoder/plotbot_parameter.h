/// Definition of encoder pins

#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H
  
//static float const meterPerRev = 6.35e-3F;
static float const meterPerClick = 6.35e-3F/20.F;

/// On/Off switches per step that would invoke the position changed callback function?
static byte const rotary_steps_per_click = 4;

#define ROTARY_PIN_X1 D0
#define ROTARY_PIN_X2 D1
#define ROTARY_PIN_Y1 D2
#define ROTARY_PIN_Y2 D5
#define ROTARY_PIN_Z1 D6
#define ROTARY_PIN_Z2 D7

#endif