/// Source file for PlotbotEncoder

#include "plotbot_encoder.h"

void PlotbotEncoder::setup()
{
  rx.begin(ROTARY_PIN_X1, ROTARY_PIN_X2, CLICKS_PER_STEP);
  ry.begin(ROTARY_PIN_Y1, ROTARY_PIN_Y2, CLICKS_PER_STEP);
  rz.begin(ROTARY_PIN_Z1, ROTARY_PIN_Z2, CLICKS_PER_STEP);
}

void PlotbotEncoder::update()
{
  rx.loop();
  ry.loop();
  rz.loop();
}

void PlotbotEncoder::getPositions(float positions[3])
{
  float const revPerMeter = 300.F; // todo: Ganghoehe oder Faktor messen
  float const factor = 1.0F / revPerMeter;

  positions[0] = static_cast<float>(rx.getPosition()) * factor;
  positions[1] = static_cast<float>(ry.getPosition()) * factor;
  positions[2] = static_cast<float>(rz.getPosition()) * factor;
}