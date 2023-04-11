#include "ESPRotary.h"
#include "PacketSerial.h"
#include "Ticker.h"

#include "PinDefinitions.h"

#define CLICKS_PER_STEP 20
#define SERIAL_SPEED    115200

/// Serial communication with COBS encoded messages
PacketSerial packetSerial;

/// Rotary encoder x-Axis
ESPRotary rx;
/// Rotary encoder y-Axis
ESPRotary ry;
/// Rotary encoder z-Axis
ESPRotary rz;

Ticker sendPositionsTicker;

/// @brief Get the position of the axis in meter
/// @param[out] positions Position of x, y, and z axis in m
void getPositions(float positions[3])
{
  float const revPerMeter = 300.F; // todo: Ganghoehe
  float const factor = 1.0F/revPerMeter;

  positions[0] = static_cast<float>(rx.getPosition()) * factor;
  positions[1] = static_cast<float>(ry.getPosition()) * factor;
  positions[2] = static_cast<float>(rz.getPosition()) * factor;
}

void sendPositions() {
  float positions[3];
  getPositions(positions);

  size_t numBytes = 12;
  packetSerial.send(reinterpret_cast<uint8_t*>(positions), numBytes); // todo: check float representation arduino vs linux PC
}


void setup() {
  Serial.begin(BAUDRATE);
  delay(50);

  rx.begin(ROTARY_PIN_X1, ROTARY_PIN_X2, CLICKS_PER_STEP);
  ry.begin(ROTARY_PIN_Y1, ROTARY_PIN_Y2, CLICKS_PER_STEP);
  rz.begin(ROTARY_PIN_Z1, ROTARY_PIN_Z2, CLICKS_PER_STEP);

  sendPositionsTicker.attach_ms(100, sendPositions); // send position with 10Hz todo: evaluate this
}

void loop() {
  rx.loop();
  ry.loop();
  rz.loop();
}